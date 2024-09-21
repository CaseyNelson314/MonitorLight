//
//   color space
//
//   copyright (c) 2024 okawa yusuke
//


#pragma once


namespace casey
{

    /**
     * @brief RGB color space
     */
    struct rgb
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        uint32_t as24bit() const
        {
            return (static_cast<uint32_t>(r) << 16) |
                   (static_cast<uint32_t>(g) << 8) |
                   (static_cast<uint32_t>(b) << 0);
        }

        /**
         * @brief kelvin -> RGB
         * @link https://github.com/mattdesl/kelvin-to-rgb/blob/master/index.js
         */
        static rgb from_kelvin(double kelvin)
        {
            double temp = kelvin / 100.0;
            double r, g, b;

            if (temp <= 66.0)
            {
                r = 255;
            }
            else
            {
                r = temp - 60.0;
                r = 329.698727446 * std::pow(r, -0.1332047592);
                r = constrain(r, 0.0, 255.0);
            }

            if (temp <= 66.0)
            {
                g = temp;
                g = 99.4708025861 * std::log(g) - 161.1195681661;
                g = constrain(g, 0.0, 255.0);
            }
            else
            {
                g = temp - 60.0;
                g = 288.1221695283 * std::pow(g, -0.0755148492);
                g = constrain(g, 0.0, 255.0);
            }

            if (temp >= 66.0)
            {
                b = 255;
            }
            else if (temp <= 19.0)
            {
                b = 0;
            }
            else
            {
                b = temp - 10.0;
                b = 138.5177312231 * std::log(b) - 305.0447927307;
                b = constrain(b, 0.0, 255.0);
            }

            return {
                static_cast<uint8_t>(Adafruit_NeoPixel::gamma8(r)),
                static_cast<uint8_t>(Adafruit_NeoPixel::gamma8(g)),
                static_cast<uint8_t>(Adafruit_NeoPixel::gamma8(b)),
            };
        }
    };


}    // namespace casey
