
// NeoPixel test program showing use of the WHITE channel for RGBW
// pixels only (won't look correct on regular RGB NeoPixel strips).

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// forward declarations
void colorRotate(uint32_t const &color, unsigned long const waitTimeMs);

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  10

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void loop()
{
    colorRotate(strip.Color(255,   0,   0), 5000); // Red
}

double brightnessFunctionMountain(double const x)
{
    double const halfWidthHalfMaximum = 2.;
    double const halfWidthHalfMaximumSqrt = sqrt(halfWidthHalfMaximum);
    double const normalization = 2. * atan(1./(2 * halfWidthHalfMaximumSqrt));
    return atan(x/halfWidthHalfMaximumSqrt) / normalization;
}

// move position to [-range/2, range/2]
double normalizePosition(double const position, double const range)
{
    return fmod(fmod(position, range) + range, range) - (range / 2.);
}

void colorRotate(uint32_t const &color, unsigned long const totalTimeMs)
{
    unsigned const numberOfPixels = strip.numPixels();
    double const numberOfPixelsDouble = static_cast<double>(numberOfPixels);
    unsigned long const startTime = millis();
    unsigned long deltaTime = 0;
    while (deltaTime < totalTimeMs)
    {
        unsigned long const curTime = millis();
        deltaTime = (curTime - startTime);
        double const deltaTimeDouble = static_cast<double>(deltaTime) / 500.;
        for(unsigned i=0; i < numberOfPixels; ++i)
        {
            double const normalizedPosition = normalizePosition(static_cast<double>(i) - deltaTimeDouble, numberOfPixelsDouble);
            double const previousBrightness = brightnessFunctionMountain(normalizedPosition-.5);
            double const nextBrightness = brightnessFunctionMountain(normalizedPosition+.5);

            double const difference = nextBrightness - previousBrightness;

            uint8_t const colorVal = static_cast<uint8_t>(255. * difference);

            uint32_t const colorMod = strip.Color(0,
                                                  0,
                                                  0,
                                                  strip.gamma8(colorVal));
            strip.setPixelColor(i, colorMod);
        }
        strip.show();
    }
}
