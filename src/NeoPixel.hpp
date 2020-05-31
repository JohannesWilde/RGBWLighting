#ifndef NEOPIXEL_HPP
#define NEOPIXEL_HPP

#include <stdint.h>

namespace NeoPixel
{

/// Color structure. Defines RGB triplet.
union ColorRGBW
{
    uint32_t value;
    struct
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t white;
    } components;
};

}

#endif // NEOPIXEL_HPP
