//
//   ライト
//
//   copyright (c) 2024 okawa yusuke
//


#pragma once

#include <Adafruit_NeoPixel.h>

#include "moving_average.hpp"
#include "color.hpp"

namespace casey
{

    class light
    {
    public:

        light(uint16_t nLED, int16_t nPin)
            : pixels{ nLED, nPin }
        {
        }

        void begin()
        {
            pixels.begin();
        }

        void update(int brightness, int kelvin)
        {
            const uint8_t write_brightness = ma_brightness(brightness);
            const uint32_t write_rgb = rgb::from_kelvin(ma_kelvin(kelvin)).as24bit();

            pixels.setBrightness(write_brightness);
            pixels.fill(write_rgb);

            pixels.show();
        }
        
    private:

        Adafruit_NeoPixel pixels;
        casey::moving_average<50> ma_kelvin{};
        casey::moving_average<50> ma_brightness{};
    };

}    // namespace casey
