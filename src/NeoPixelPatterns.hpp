#ifndef NEOPIXELPATTERNS_HPP
#define NEOPIXELPATTERNS_HPP

#include <math.h>
#include <Adafruit_NeoPixel.h>


namespace NeoPixelPatterns
{

double brightnessFunctionMountain(double const x);

// move position to [-range/2, range/2)
double normalizePosition(double const position, double const range);

template<size_t numberOfPixels>
void updateStrip(Adafruit_NeoPixel & strip, double const currentTime)
{
    double const numberOfPixelsDouble = static_cast<double>(numberOfPixels);
    for(unsigned i=0; i < numberOfPixels; ++i)
    {
        double const normalizedPosition = normalizePosition(static_cast<double>(i) - currentTime, numberOfPixelsDouble);
        double const previousBrightness = brightnessFunctionMountain(normalizedPosition-.5);
        double const nextBrightness = brightnessFunctionMountain(normalizedPosition+.5);

        double const difference = nextBrightness - previousBrightness;

        uint8_t const colorVal = static_cast<uint8_t>(255. * difference);

        uint32_t const colorMod = Adafruit_NeoPixel::Color(0,
                                              0,
                                              0,
                                              Adafruit_NeoPixel::gamma8(colorVal));
        strip.setPixelColor(i, colorMod);
    }
    strip.show();
}

template<size_t numberOfPixels>
void colorRotate(uint32_t const &color, unsigned long const totalTimeMs, Adafruit_NeoPixel & strip)
{
    unsigned long const startTime = millis();
    unsigned long deltaTime = 0;
    while (deltaTime < totalTimeMs)
    {
        unsigned long const curTime = millis();
        deltaTime = (curTime - startTime);
        double const deltaTimeDouble = static_cast<double>(deltaTime) / 500.;
        updateStrip<numberOfPixels>(strip, deltaTimeDouble);
    }
}

} // NeoPixelPatterns

#endif // NEOPIXELPATTERNS_HPP
