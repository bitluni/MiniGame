/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */

#include <ESP8266WiFi.h> 
#include <Wire.h>

#include "Sound.h"
#include "Graphics.h"
#include "Sprite.h"
#include "Paddle.h"
#include "Ball.h"
#include "Environment.h"
#include <EEPROM.h>

/************************* SETUP *********************************/
const int oledJumper = 0;  // I2C 0=0x3C, 1=0x3D
const int USE_STANDBY = true;
/************************* Other settings ****************************/
/*
const int D0 = 16;
const int D1 = 5;     //oled
const int D2 = 4;     //oled
const int D3 = 0;     //button base
const int D4 = 2;     //led
const int D5 = 14;    //buzzer
const int D6 = 12;    
const int D7 = 13;
const int D8 = 15;    //pull down
*/

//4,5,12,13,14 and 16

Sound sound(D5);
Graphics oled(oledJumper);
Environment environment(oled, sound);

void setup()
{
  //Serial.begin(115200);
  oled.begin();
  oled.clear(ALL);
  oled.display();

  if(USE_STANDBY)
  {
    EEPROM.begin(4);
    unsigned char onOff = EEPROM.read(0);
    onOff = onOff ? 0 : 255;
    EEPROM.write(0, onOff);
    EEPROM.commit();
    if(onOff)
    {
      ESP.deepSleep(0, WAKE_RF_DISABLED); 
    }
  }
    
  pinMode(D6, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
}

float fps = 0;
unsigned int oldTime = 0;
void loop()
{
  unsigned int t = millis();
  float dt = (t - oldTime) * 0.001;
  fps = fps * 0.9f + 0.1f * 1000.0f / (t - oldTime);
  oldTime = t;
  oled.clear(PAGE);
  oled.setCursor(0, 0);
  //oled.print(fps);
  //oled.println("fps");
  environment.move(dt);
  environment.draw();
  oled.display();
  sound.process(t);
}
