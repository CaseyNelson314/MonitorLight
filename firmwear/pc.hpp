//
//   PC との通信
//
//   copyright (c) 2024 okawa yusuke
//


#pragma once

#include <optional>

namespace casey
{

    class pc
    {
    public:
        struct config
        {
            uint8_t brightness;
            uint16_t kelvin;
        };


        void begin()
        {
            Serial.begin();
        }


        void set_current_config(const config& config)
        {
            current_config = config;
        }


        std::optional<config> get_request_config() const
        {
            if (request)
            {
                return request_config;
            }
            return std::nullopt;
        }


        void update()
        {
            request = false;

            while (Serial.available())
            {
                const char mode = Serial.read();

                switch (mode)
                {

                case 'w':    // write parameter (format: "w <brightness> <kelvin>")
                {
                    (void)Serial.read();  // ' '
                    
                    int brightness = Serial.parseInt();
                    if (0 <= brightness and brightness <= UINT8_MAX)
                    {
                        request_config.brightness = brightness;
                        request = true;
                    }
                    else
                    {
                        Serial.println("ng");
                        break;
                    }

                    (void)Serial.read();  // ' '
                    
                    int kelvin = Serial.parseInt();
                    if (0 <= kelvin and kelvin <= UINT16_MAX)
                    {
                        request_config.kelvin = kelvin;
                        request = true;
                    }
                    else
                    {
                        Serial.println("ng");
                        break;
                    }

                    Serial.println("ok");
                    break;
                }

                case 'r':    // request current parameter (format: "r")
                {
                    Serial.print(current_config.brightness);
                    Serial.print(' ');
                    Serial.println(current_config.kelvin);
                    break;
                }

                default:
                {
                    Serial.println("ng");
                }
                }

                while (Serial.available())
                    (void)Serial.read();
            }
        }

    private:
        bool request{};

        config current_config{};
        config request_config{};
    };

}    // namespace casey
