
#include <Arduino.h>
#include "gui.hpp"

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
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

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

    Driver::RelaisDriver<25, Driver::RelaisStateOn> powerRelais(Driver::RelaisStateOff);

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

        if ((curTime - latestRelaisToggleTime) >= relaisTogglePeriod)
        {
            powerRelais.toggle();
            latestRelaisToggleTime = curTime;
        }

        double const deltaTimeDouble = static_cast<double>(deltaTime) / 500.;
        NeoPixelPatterns::updateStrip<LED_COUNT, NeoPixelPatterns::brightnessFunctionMountain>(strip, Adafruit_NeoPixel::Color(0, 0, 0, 255), deltaTimeDouble);


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

