/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#pragma once
#include <SFE_MicroOLED.h>

class Graphics: public MicroOLED
{
  public:
  uint8_t *offscreen;
  
  Graphics(int jumper);
  void display();
};

