
#include <Arduino.h>
#include "gui.hpp"
#include "NeoPixel.hpp"

// Define debug message function
static int16_t DebugOut(char ch) { if (ch == (char)'\n') Serial.println(""); else Serial.write(ch); return 0; }


// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

#include "NeoPixelPatterns.hpp"
#include "RelaisDriver.hpp"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     27

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  10

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50

// Declare our NeoPixel strip object:
static Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
static Driver::RelaisDriver<25, Driver::RelaisStateOn> powerRelais(Driver::RelaisStateOff);
static NeoPixel::ColorRGBW ledColor = { .components={0, 0, 0, 255} };

void setup()
{
    // ------------------------------------------------
    // Initialize
    // ------------------------------------------------
    Serial.begin(9600);
    // Wait for USB Serial
    //delay(1000);  // NOTE: Some devices require a delay after Serial.begin() before serial port can be used

    gslc_InitDebug(&DebugOut);

    // ------------------------------------------------
    // Create graphic elements
    // ------------------------------------------------
    InitGUIslice_gen();

    // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
    // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
#endif
    // END of Trinket-specific code.

    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)

    unsigned long const relaisTogglePeriod = 5000;
    unsigned long const startTime = millis();

    unsigned long latestRelaisToggleTime = startTime - relaisTogglePeriod;
    powerRelais.turnOn();
    while (true)
    {
        unsigned long const curTime = millis();
        unsigned long deltaTime = (curTime - startTime);

//        if ((curTime - latestRelaisToggleTime) >= relaisTogglePeriod)
//        {
//            powerRelais.toggle();
//            latestRelaisToggleTime = curTime;
//        }

        double const deltaTimeDouble = static_cast<double>(deltaTime) / 500.;
        NeoPixelPatterns::updateStrip<LED_COUNT, NeoPixelPatterns::brightnessFunctionMountain>(strip,  ledColor.value, deltaTimeDouble);


        // ------------------------------------------------
        // Update GUI Elements
        // ------------------------------------------------

        //TODO - Add update code for any text, gauges, or sliders

        // ------------------------------------------------
        // Periodically call GUIslice update function
        // ------------------------------------------------
        gslc_Update(&m_gui);
    }

}

// -----------------------------------
// Main event loop
// -----------------------------------
void loop()
{
    // Should never be reached.
}


// ------------------------------------------------
// Callback Methods
// ------------------------------------------------

// Common Button callback
bool CbBtnCommon(void* pvGui,void *pvElemRef,gslc_teTouch eTouch,int16_t nX,int16_t nY)
{
    // Typecast the parameters to match the GUI and element types
    gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

    Serial.print("Button pressed: ");

    if ( eTouch == GSLC_TOUCH_UP_IN ) {
        // From the element's ID we can determine which button was pressed.
        switch (pElem->nId) {
        //<Button Enums !Start!>
        case E_BTN_BACKLIGHT_DECREASE:
            Serial.print("Backlight decrease\n");
            break;
        case E_BTN_BACKLIGHT_INCREASE:
            Serial.print("Backlight increase\n");
            break;
        case E_BTN_LED_BRIGHTNESS_DECREASE:
            Serial.print("Led brightness decrease\n");
            strip.setBrightness(strip.getBrightness() - 1);
            gslc_ElemXSliderSetPos(pGui, m_pSliderLedBrightness, strip.getBrightness());
            break;
        case E_BTN_LED_BRIGHTNESS_INCREASE:
            Serial.print("Led brightness increase\n");
            strip.setBrightness(strip.getBrightness() + 1);
            gslc_ElemXSliderSetPos(pGui, m_pSliderLedBrightness, strip.getBrightness());
            break;
            //<Button Enums !End!>
        default:
            break;
        }
    }
    return true;
}

// Callback function for when a slider's position has been updated
bool CbSlidePos(void* pvGui,void* pvElemRef,int16_t nPos)
{
    gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
    gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

    // From the element's ID we can determine which slider was updated.
    switch (pElem->nId) {
    //<Slider Enums !Start!>
    case E_SLIDER_LED_RED:
    case E_SLIDER_LED_GREEN:
    case E_SLIDER_LED_BLUE:
    {
        // Fetch the slider position
        uint8_t const red = gslc_ElemXSliderGetPos(pGui,m_pSliderLedRed);
        uint8_t const green = gslc_ElemXSliderGetPos(pGui,m_pSliderLedGreen);
        uint8_t const blue = gslc_ElemXSliderGetPos(pGui,m_pSliderLedBlue);
        // Calculate the new RGB value
        gslc_tsColor const colRGB = (gslc_tsColor){red, green, blue};
        // Update the color box
        gslc_ElemSetCol(pGui, m_pBoxLedColor, GSLC_COL_WHITE, colRGB, GSLC_COL_WHITE);
        ledColor.components.red = red;
        ledColor.components.green = green;
        ledColor.components.blue = blue;
        break;
    }
    case E_SLIDER_LED_BRIGHTNESS:
    {
        uint8_t const brightness = gslc_ElemXSliderGetPos(pGui,m_pSliderLedBrightness);
        strip.setBrightness(brightness);
        break;
    }
    //<Slider Enums !End!>
    default:
    {
        break;
    }
    }

    return true;
}

bool CbCheckbox(void* pvGui, void* pvElemRef, int16_t nSelId, bool bState)
{
    // Typecast the parameters to match the GUI and element types
//    gslc_tsGui*     pGui     = (gslc_tsGui*)(pvGui);
//    gslc_tsElemRef* pElemRef = (gslc_tsElemRef*)(pvElemRef);
//    gslc_tsElem*    pElem    = gslc_GetElemFromRef(pGui,pElemRef);

    Serial.print("Check Box pressed: ");

    Serial.print(bState ? "on " : "off ");

    Serial.print(nSelId);
    Serial.print(" ");

    // From the element's ID we can determine which button was pressed.
    switch (nSelId)
    {
    //<CheckBox Enums !Start!>
    case E_CHECK_POWER:
    {
        Serial.print("power\n");
        break;
    }
    case E_CHECK_RELAIS:
    {
        Serial.print("relais\n");
        break;
    }
    case E_CHECK_BACKLIGHT:
    {
        Serial.print("backlight\n");
        break;
    }
    case E_CHECK_LED_BRIGHTNESS:
    {
        Serial.print("led\n");
        break;
    }
    //<Button Enums !End!>
    default:
    {
        break;
    }
    }
    return true;
}

