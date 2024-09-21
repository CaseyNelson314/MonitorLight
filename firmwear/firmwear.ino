//
//   firmwear / M5StampC3U <https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json>
//
//   copyright (c) 2024 okawa yusuke
//


#include <Preferences.h>
#include "light.hpp"
#include "websocket_server.hpp"
#include "key.hpp"

static int brightness;
static int kelvin;

static casey::light light{ /*nLED = */ 13 , /*nPin = */ 10 };
static casey::websocket_server websocket{ /*port = */ 443 };

static Preferences preferences;


/**
 * @brief write parameter (format: "w <brightness> <kelvin>", res: "OK" or "NG")
 */
std::string on_request_write_parameter(const std::string& request)
{
    int tmp_brightness;
    int tmp_kelvin;

    const int n_item = sscanf(request.c_str(), "w %d %d", &tmp_brightness, &tmp_kelvin);
    if (n_item != 2)
        return "NG";

    if (not(0 <= tmp_brightness and tmp_brightness <= 255))
        return "NG";

    if (not(0 <= tmp_kelvin and tmp_kelvin <= 12000))
        return "NG";

    brightness = tmp_brightness;
    kelvin = tmp_kelvin;

    return "OK";
}


/**
 * @brief read parameter (req: "r", res: "<brightness> <kelvin>")
 */
std::string on_request_read_parameter()
{
    return std::to_string(brightness) + ' ' + std::to_string(kelvin);
}


/**
 * @brief save parameter to flush mem (format: "s", res: "OK" or "NG")
 */
std::string on_request_save_parameter()
{
    static uint32_t prev_save_ms;
    if (millis() - prev_save_ms > 1000)
    {
        preferences.putUInt("brightness", brightness);
        preferences.putUInt("kelvin", kelvin);
        prev_save_ms = millis();
        return "OK";
    }
    else
    {
        Serial.println("~~U_ (^^ ) 高速書き換え絶対に許さないマン ( ^^) _U~~");
        return "NG";
    }
}


std::string on_request(const std::string& request)
{
    if (request.size())
    {
        switch (request.front())
        {
        case 'w': return on_request_write_parameter(request);
        case 'r': return on_request_read_parameter();
        case 's': return on_request_save_parameter();
        }
    }
    return "NG";
}


void setup()
{
    Serial.begin();
    
    preferences.begin("light-conf", false);
    brightness = preferences.getUInt("brightness", 100);
    kelvin = preferences.getUInt("kelvin", 9000);
    
    casey::begin_wifi(ssid, password);
    casey::begin_mdns("m5stamp");

    light.begin();
    websocket.begin(on_request);
}


void loop()
{
    websocket.update();
    light.update(brightness, kelvin);
    delay(10);
}
