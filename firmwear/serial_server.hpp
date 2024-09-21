//
//   serial client
//
//   copyright (c) 2024 okawa yusuke
//

#pragma once

namespace casey
{
    
    class serial_server
    {
    public:
        using request_handler_t = std::string (*)(const std::string&);

        serial_server(uint16_t port)
            : websocket(port)
        {
        }

        void begin(request_handler_t handler)
        {
            request_handler = handler;
            Serial.begin();
        }
        
        void update()
        {
            while (Serial.available())
            {
                const char c = Serial.read();
                if (c == '\n')
                {
                    const auto&& respons = request_handler(request_string);

                    for (auto&& c : respons)
                        Serial.write(c);
                    Serial.println();

                    request_string.clear();
                }
                else
                {
                    if (request_string.size() > 256)
                        continue;
                    request_string += c;
                }
            }
        }

    private:

        std::string request_string;
        request_handler_t request_handler;
    };

}