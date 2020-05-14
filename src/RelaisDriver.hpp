#ifndef RELAIS_DRIVER_HPP
#define RELAIS_DRIVER_HPP

#include <Arduino.h>

namespace Driver
{

enum RelaisState
{
    RelaisStateOn,
    RelaisStateOff
};

} // namespace Driver


namespace
{

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


template<Driver::RelaisState relaisStateWhenLow>
uint8_t relaisStateToPinValue(Driver::RelaisState const relaisState)
{
    return (relaisStateWhenLow == relaisState) ? LOW : HIGH;
}


template<Driver::RelaisState relaisStateWhenLow>
Driver::RelaisState pinValueToRelaisState(uint8_t const pinValue)
{
    return (LOW == pinValue) ? relaisStateWhenLow : switchedRelaisState<relaisStateWhenLow>();
}

} // anonymous namespace


namespace Driver
{

template<uint8_t pinNumber, RelaisState relaisStateWhenLow>
class RelaisDriver
{
public:
    RelaisDriver(RelaisState const relaisStateInitial)
    {
        pinMode(pinNumber, OUTPUT);
        setRelaisState(relaisStateInitial);
    }

    ~RelaisDriver()
    {
        pinMode(pinNumber, INPUT);
    }

    void turnOn()
    {
        setRelaisState(RelaisStateOn);
    }

    void turnOff()
    {
        setRelaisState(RelaisStateOff);
    }

    void toggle()
    {
        digitalWrite(pinNumber, !digitalRead(pinNumber));
    }

    void setRelaisState(RelaisState const relaisState)
    {
        digitalWrite(pinNumber, ::relaisStateToPinValue<relaisStateWhenLow>(relaisState));
    }

    RelaisState getRelaisState()
    {
        return ::pinValueToRelaisState<relaisStateWhenLow>(digitalRead(pinNumber));
    }
};


} // namespace Driver

#endif // RELAIS_DRIVER_HPP
