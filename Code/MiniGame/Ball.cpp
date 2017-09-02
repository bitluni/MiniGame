/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include "Environment.h"
#include "Ball.h"
#include "Sprite.h"

const unsigned char SPRITE_BALL_NORMAL[] = {
  3, 3,
  0, 255, 0,
  255, 0, 255,
  0, 255, 0,
  1, 1,
};

Sprite spriteBallNormal(SPRITE_BALL_NORMAL);

Ball::Ball(Environment& e)
:environment(e)
{
  reset();
}

Ball::Ball(Environment& e, float startX, float startY, float startVx, float startVy)
:environment(e)
{
  x = startX;
  y = startY;
  vx = startVx;
  vy = startVy;
  speed = 14;
  normalize();
}

void Ball::reset()
{
  x = environment.XRES * 0.5f;
  y = environment.YRES - 3;
  vx = 25;
  vy = -33;
  speed = 50;
  normalize();
  status = STATUS_ACTIVE;
}

void Ball::normalize()
{
  float l = vx * vx + vy * vy;
  if(l == 0) return;
  l = 1.f / sqrt(l) * speed;
  vx *= l;
  vy *= l;
}

void Ball::draw()
{
  if(status != STATUS_ACTIVE) return;
  spriteBallNormal.draw(environment.graphics, int(x + 0.5f), int(y + 0.5f));
}

void Ball::move(float dt)
{
  if(status != STATUS_ACTIVE) return;
  float nx = x + vx * dt;
  float ny = y + vy * dt;
  if(nx < 0)
  {
    nx = 0;
    vx = -vx;
    environment.sound.beep(800, 10);
    return;
  }
  if(nx > environment.XRES - 1)
  {
    nx = environment.XRES - 1;
    vx = -vx;
    environment.sound.beep(800, 10);
    return;
  }
  if(ny < 0)
  {
    ny = 0;
    vy = -vy;
    environment.sound.beep(800, 10);
    return;
  }
  if(ny > environment.YRES - 1)
  {
    //ny = environment.YRES - 1;
    //vy = -vy;
    status = STATUS_INACTIVE;
    environment.sound.beep(400, 500);
    return;
  }
  
  if(vy > 0 && environment.player.hit(x, y))
  {
    environment.player.reflect(*this);
    return;
  }
  
  x = nx;
  y = ny;
}
