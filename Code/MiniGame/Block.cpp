/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include "Block.h"
#include "Sprite.h"
#include "Environment.h"

const unsigned char SPRITE_TYPE_BASIC[] = {
  8, 3,
  255, 255, 255, 255, 255, 255, 255, 255,
  255, 0, 0, 0, 0, 0, 0, 255,
  255, 255, 255, 255, 255, 255, 255, 255,
  0, 0,
};
const unsigned char SPRITE_TYPE_SOLID[] = {
  8, 3,
  255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255,
  0, 0,
};
const unsigned char SPRITE_TYPE_HARD2[] = {
  8, 3,
  255, 255, 255, 255, 255, 255, 255, 255,
  255, 0, 255, 0, 255, 0, 255, 128,
  255, 255, 255, 255, 255, 255, 255, 255,
  0, 0,
};
const unsigned char SPRITE_TYPE_SPAWN11[] = {
  8, 3,
  0, 255, 255, 0, 0, 255, 255, 0,
  255, 0, 0, 255, 255, 0, 0, 255,
  0, 255, 255, 0, 0, 255, 255, 0,
  0, 0,
};
const unsigned char SPRITE_TYPE_SPAWN22[] = {
  8, 3,
  0, 255, 0, 255, 255, 0, 255, 0,
  255, 0, 255, 0, 0, 255, 0, 255,
  0, 255, 0, 255, 255, 0, 255, 0,
  0, 0,
};

const unsigned char SPRITE_TYPE_DUMMY[] = {
  8, 3,
  255, 0, 0, 0, 0, 0, 0, 255,
  0, 0, 0, 0, 0, 0, 0, 0,
  255, 0, 0, 0, 0, 0, 0, 255,
  0, 0,
};

Sprite spriteTypeBasic(SPRITE_TYPE_BASIC);
Sprite spriteTypeSolid(SPRITE_TYPE_SOLID);
Sprite spriteTypeHard1(SPRITE_TYPE_HARD2);
Sprite spriteTypeHard2(SPRITE_TYPE_HARD2);
Sprite spriteTypeSpawn11(SPRITE_TYPE_SPAWN11);
Sprite spriteTypeSpawn21(SPRITE_TYPE_SPAWN22);
Sprite spriteTypeSpawn22(SPRITE_TYPE_SPAWN22);
Sprite spriteTypeDummy(SPRITE_TYPE_DUMMY);

Sprite *blockSprite[] = {0, &spriteTypeBasic, &spriteTypeSolid, &spriteTypeHard1, &spriteTypeHard2, 0, &spriteTypeSpawn11, 0, &spriteTypeSpawn21, &spriteTypeSpawn22};

Block::Block()
{
  
}

void Block::init(Environment &e, int t, int x, int y)
{
  this->x = x;
  this->y = y;
  environment = &e;
  type = t;
}

void Block::degrade()
{
  const int score[] = {
    0,    
    10,
    0,
    20,
    0,
    0,
    5,
    0,
    10,
    0
    };
  const int sound[] = {
    0,    
    200,
    2000,
    200,
    300,
    180,
    260,
    180,
    260,
    420,
    };
  const int newType[] = {
    TYPE_GONE, 
    TYPE_GONE, 
    TYPE_SOLID,
    TYPE_GONE,
    TYPE_HARD1,
    TYPE_SPAWN10,
    TYPE_SPAWN10,
    TYPE_SPAWN20,
    TYPE_SPAWN20,
    TYPE_SPAWN21
    };
    environment->sound.beep(sound[type], 20);
    environment->score += score[type];

    if(type != newType[type])
    {
      type = newType[type];
      if(type == TYPE_SPAWN10 || type == TYPE_SPAWN20)
        timer = SPAWN_TIME;
    }
}

bool Block::destroy()
{
  
}

void Block::move(float dt)
{
  if(type == TYPE_SPAWN10 || type == TYPE_SPAWN20)
  {
    timer -= dt;
    if(timer <= 0)
    {
        if(type == TYPE_SPAWN10)
          type = TYPE_SPAWN11;
        if(type == TYPE_SPAWN20)
          type = TYPE_SPAWN22;
    }
  }
}

void Block::draw()
{
  if(blockSprite[type] != 0)
    blockSprite[type]->draw(environment->graphics, x * WIDTH, y * HEIGHT);  
}

bool Block::hit(float bx, float by)
{
  if(!isVisible()) return false;
  if(bx < x * WIDTH || bx >= (x * WIDTH + WIDTH) || by < y * HEIGHT || by >= (y * HEIGHT + HEIGHT)) return false;
  return true;
}

void Block::reflect(Ball& b)
{
  int rx = (b.x + 0.5f) - x * WIDTH;
  int ry = (b.y + 0.5f) - y * HEIGHT;
  
  if(rx == 0)
  {
    if(b.vx > 0)
    {
      b.vx = -b.vx;
      degrade();
    }
    /*if(ry == 0)
    {
      if(b.vx > 0)
      {
        b.vx = -b.vx;
      }
    }
    else if(ry == HEIGHT - 1)
    {
    }*/
  }
  else
  if(rx == WIDTH - 1)
  {
/*    if(ry == 0)
    {
    }
    else if(ry == HEIGHT - 1)
    {
    }*/
    if(b.vx < 0)
    {
      b.vx = -b.vx;
      degrade();
    }
  }
  if(ry == 0)
  {
    if(b.vy > 0)
    {
      b.vy = -b.vy;
      degrade();
    }
  }
  else if(ry == HEIGHT - 1)
  {
    if(b.vy < 0)
    {
      b.vy = -b.vy;
      degrade();
    }
  }
}

bool Block::isVisible()
{
  return blockSprite[type] != 0;
}

bool Block::irelevant()
{
  const bool win[] = {true, false, true, false, false, true, true, true, true, true};
  return win[type];
}


