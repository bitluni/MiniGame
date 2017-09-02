/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include "Sprite.h"

Sprite::Sprite(const unsigned char *data)
{
  this->data = data;
  sx = data[0];
  sy = data[1];
  sprite = data + 2;
  points = sprite + sx * sy;
  cx = points[0];
  cy = points[1];
}

void Sprite::draw(Graphics& g, int x, int y, int layer)
{
  for(int j = 0; j < sy; j++)
    for(int i = 0; i < sx; i++)
    {
      int ax = x + i - cx; 
      int ay = y + j - cy;
      int p = sprite[j * sx + i];
      if(p & (1 << LAYER_OPACITY))
        g.pixel(ax, ay, p & (1 << layer), NORM);
    }
}

bool Sprite::hit(int x, int y, int layer)
{
  x += cx;
  y += cy;
  if(x < 0 || y < 0 || x >= sx || y >= sy) return false;
  return sprite[y * sx + x] & (1 << layer) > 0;
}
