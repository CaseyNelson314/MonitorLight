//
//   ファームウエア / Raspberry Pi Pico
//
//   copyright (c) 2024 okawa yusuke
//


#include "light.hpp"

static Adafruit_NeoPixel pixel{ 13 /*nLED*/, 0 /*nPin*/, NEO_GRB + NEO_KHZ800 };

static casey::light light{ pixel };

void setup()
{
    Serial.begin();
    light.begin();
}

void loop()
{
    light.update();
    delay(10);
}
