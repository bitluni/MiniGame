/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include "Graphics.h"

static const int SCREEN_BYTES = 384;
static uint8_t screen[SCREEN_BYTES];

Graphics::Graphics(int jumper)
  :MicroOLED(255, jumper)
{
  offscreen = getScreenBuffer();
  for(int i = 0; i < SCREEN_BYTES; i++)
    screen[i] = offscreen[i];
}

void Graphics::display()
{
  uint8_t i, j;
  for (i = 0; i < 6; i++) 
  {
    setPageAddress(i);
    bool columnSet = false;
    for (j = 0 ;j < 0x40; j += 2) 
    {
      int addr = i * 0x40 + j;
      if(offscreen[addr] != screen[addr] || offscreen[addr + 1] != screen[addr + 1])
      {
        screen[addr] = offscreen[addr];
        screen[addr + 1] = offscreen[addr + 1];
        if(!columnSet)
        {
          setColumnAddress(j);
          columnSet = true;
        } 
        data(screen[addr]);
        data(screen[addr + 1]);
      }
      else
        columnSet = false;
    }
  }
}

