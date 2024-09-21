//
//   wifi client
//
//   copyright (c) 2024 okawa yusuke
//

#include <string>

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebSocketsServer.h>

#pragma once


namespace casey
{

    void begin_wifi(const char* ssid, const char* password)
    {
        WiFi.begin(ssid, password);
        Serial.print("Connecting to WiFi");
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(100);
            Serial.print(".");
        }
        Serial.println(" connected");
    }

    void begin_mdns(const char* hostname)
    {
        if (not MDNS.begin(hostname))
        {
            Serial.println("Error setting up MDNS responder!");
            for (;;);
        }
        Serial.println("mDNS responder started");
    }

    class websocket_server
    {
    public:
        using request_handler_t = std::string (*)(const std::string&);

        websocket_server(uint16_t port)
            : websocket(port)
        {
        }

        void begin(request_handler_t handler)
        {
            request_handler = handler;
            Serial.begin();

            websocket.begin();
            websocket.onEvent([this](uint8_t /*socket_id*/, WStype_t type, uint8_t* payload, size_t length)
                              {
                                if (type == WStype_TEXT) {
                                    on_request(std::string{ (char*)payload, length });
                                } });
        }

        void on_request(const std::string& req)
        {
            Serial.println(req.c_str());
            request_handler(req.c_str());
        }

        void update()
        {
            websocket.loop();

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
        WebSocketsServer websocket;

        std::string request_string;
        request_handler_t request_handler;
    };
}    // namespace casey