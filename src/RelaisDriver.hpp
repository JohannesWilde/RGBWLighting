#ifndef RELAIS_DRIVER_HPP
#define RELAIS_DRIVER_HPP

#include <Arduino.h>

namespace Driver
{

enum RelaisState
{
    RelaisStateOn,   // the relais is closed, current can flow
    RelaisStateOff   // the relais is opened, no connection
};

} // namespace Driver


// private helper methods
namespace
{

/**
 * Template method, to determine the inverse of the provided relaisState.
 */
template<Driver::RelaisState relaisState>
Driver::RelaisState switchedRelaisState();

template<>
Driver::RelaisState switchedRelaisState<Driver::RelaisStateOn>()
{
    return Driver::RelaisStateOff;
}

template<>
Driver::RelaisState switchedRelaisState<Driver::RelaisStateOff>()
{
    return Driver::RelaisStateOn;
}


/**
 * Determine the digital pin value [HIGH or LOW] to apply, as to achieve the desired relaisState.
 */
template<Driver::RelaisState relaisStateWhenLow>
uint8_t relaisStateToPinValue(Driver::RelaisState const relaisState)
{
    return (relaisStateWhenLow == relaisState) ? LOW : HIGH;
}


/**
 * Determine the relais state from a measured digital pin value [HIGH or LOW].
 */
template<Driver::RelaisState relaisStateWhenLow>
Driver::RelaisState pinValueToRelaisState(uint8_t const pinValue)
{
    return (LOW == pinValue) ? relaisStateWhenLow : switchedRelaisState<relaisStateWhenLow>();
}

} // anonymous namespace


namespace Driver
{

/**
 * Simple wrapper for using a relais via a digital output pin of the microcontroller.
 *
 * The pinNumber is the integer representation used by the Arduino environment.
 * The relaisStateWhenLow is the state, if LOW is applied to pinNumber [configured as OUTPUT].
 */
template<uint8_t pinNumber, RelaisState relaisStateWhenLow>
class RelaisDriver
{
public:
    /**
     * @brief RelaisDriver Simple constructor with an initial relaisState.
     * @param relaisStateInitial The initial relaisState after construction.
     */
    RelaisDriver(RelaisState const relaisStateInitial)
    {
        setRelaisState(relaisStateInitial);
        pinMode(pinNumber, OUTPUT);
    }

    /**
     * This constructor will configure pinNumber as INPUT - i.e. the pin will be free-floating afterwards.
     */
    ~RelaisDriver()
    {
        pinMode(pinNumber, INPUT);
    }

    /**
     * @brief turnOn Convenience method for setting RelaisStateOn.
     */
    void turnOn()
    {
        setRelaisState(RelaisStateOn);
    }

    /**
     * @brief turnOff Convenience method for setting RelaisStateOff.
     */
    void turnOff()
    {
        setRelaisState(RelaisStateOff);
    }

    /**
     * @brief toggle Toggles the current RelaisState.
     */
    void toggle()
    {
        digitalWrite(pinNumber, !digitalRead(pinNumber));
    }

    /**
     * @brief setRelaisState Sets the relais state to relaisState.
     * @param relaisState The relais state to set.
     */
    void setRelaisState(RelaisState const relaisState)
    {
        digitalWrite(pinNumber, ::relaisStateToPinValue<relaisStateWhenLow>(relaisState));
    }

    /**
     * @brief getRelaisState Query the current relais state from pinNumber.
     * @return The current relais state.
     */
    RelaisState getRelaisState()
    {
        return ::pinValueToRelaisState<relaisStateWhenLow>(digitalRead(pinNumber));
    }
};


} // namespace Driver

#endif // RELAIS_DRIVER_HPP
