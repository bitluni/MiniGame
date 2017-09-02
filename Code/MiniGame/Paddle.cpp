/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include "Environment.h"
#include "Paddle.h"
#include "Sprite.h"

const unsigned char SPRITE_PADDLE_NORMAL[] = {
  11, 2,
  0, 255, 255,  255, 255, 255,  255, 255, 255, 255, 0,
  255, 255, 255,  255, 255, 255,  255, 255, 255, 255, 255,
  6, 1,
};

Sprite spritePaddleNormal(SPRITE_PADDLE_NORMAL);

Paddle::Paddle(Environment &e)
:environment(e)
{
  x = e.XRES * 0.5f;
  y = e.YRES - 1;
  speed = 70.f;
  width = spritePaddleNormal.sx;
}

void Paddle::draw()
{
  spritePaddleNormal.draw(environment.graphics, int(x + 0.5f), int(y + 0.5f));
}

void Paddle::left(float dt)
{
  x -= dt * speed;
  float minx = width * 0.5f;
  if(x < minx) x = minx;
}

void Paddle::right(float dt)
{
  x += dt * speed;
  float maxx = environment.XRES - 1 - width * 0.5f;
  if(x > maxx) x = maxx;
}

bool Paddle::hit(float bx, float by)
{
  return spritePaddleNormal.hit(int(bx - x + 0.5f), int(by - y + 0.5f));
}

float Paddle::corner(float bx)
{
  float cl = bx - (x - width * 0.5f);
  float cr = (x + width * 0.5f) - bx;
  if(cl >= 0 && cl <= 3)
    return cl - 3;
  if(cr >= 0 && cr <= 3)
    return 3 - cr;
  return 0;
}

void Paddle::reflect(Ball& b)
{
  if(b.vy < 0) return;
  b.vx +=  (b.x - x) / width * 70;
  b.vy = -b.vy;
  b.normalize();
  environment.sound.beep(1200, 20);
}

