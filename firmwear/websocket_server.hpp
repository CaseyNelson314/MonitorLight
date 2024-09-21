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

    inline void begin_wifi(const char* ssid, const char* password)
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

    inline void begin_mdns(const char* hostname)
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
            websocket.begin();
            websocket.onEvent([this](uint8_t socket_id, WStype_t type, uint8_t* payload, size_t length)
                              {
                                if (type == WStype_TEXT) {
                                    const auto res = this->request_handler(std::string{ (char*)payload, length });
                                    websocket.sendTXT(socket_id, res.c_str());
                                } });
        }

        void update()
        {
            websocket.loop();
        }

    private:
        WebSocketsServer websocket;
        request_handler_t request_handler;
    };
}    // namespace casey
