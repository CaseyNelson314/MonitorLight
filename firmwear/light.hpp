//
//   ライト
//
//   copyright (c) 2024 okawa yusuke
//


#pragma once

#include <Adafruit_NeoPixel.h>

#include "moving_average.hpp"
#include "color.hpp"
#include "pc.hpp"

namespace casey
{

    class light
    {
        Adafruit_NeoPixel& pixels;

        uint16_t kelvin{ 6000 };
        casey::moving_average<100> ma_kelvin{};

        uint8_t brightness{ 100 };
        casey::moving_average<100> ma_brightness{ 100 };

        casey::pc pc{};

    public:
        light(Adafruit_NeoPixel& pixels)
            : pixels(pixels)
        {
        }

        void begin()
        {
            pixels.begin();
        }

        void update()
        {
            pc.update();
            pc.set_current_config({
                .brightness = brightness,
                .kelvin = kelvin,
            });

            if (const auto request = pc.get_request_config())
            {
                brightness = request->brightness;
                kelvin = request->kelvin;
            }

            const uint8_t write_brightness = ma_brightness(brightness);
            const uint32_t write_rgb = rgb::from_kelvin(ma_kelvin(kelvin)).as24bit();

            pixels.setBrightness(write_brightness);
            pixels.fill(write_rgb);

            pixels.show();
        }
    };

}    // namespace casey
