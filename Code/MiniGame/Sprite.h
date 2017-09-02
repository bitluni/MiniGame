/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#pragma once
#include "Graphics.h" 
class Sprite
{
  public:
  const unsigned char *data;
  const unsigned char *sprite;
  int sx, sy;
  int cx, cy;
  const unsigned char *points;

  const int LAYER_OPACITY = 7;
  
  Sprite(const unsigned char *data);
  void draw(Graphics& g, int x, int y, int layer = 0);
  bool hit(int x, int y, int layer = 1);
};

