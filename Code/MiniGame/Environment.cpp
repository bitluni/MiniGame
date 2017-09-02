/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include "Environment.h"
#include "Block.h"
#include "Levels.h"

const int BLOCK_COLUMNS = 8;
const int BLOCK_ROWS = 10;
const int BLOCK_COUNT = BLOCK_COLUMNS * BLOCK_ROWS;
Block blocks[BLOCK_COUNT];

Environment::Environment(Graphics& g, Sound& s)
  :XRES(g.getLCDWidth()),
  YRES(g.getLCDHeight()),
  ball(*this),
  player(*this),
  graphics(g),
  sound(s)
{
  startGame();
}

void Environment::startGame()
{
  score = 0;
  level = 0;
  lives = 3;
  initLevel();
  ball.reset();
  ready();
}

void Environment::ready()
{
    status = STATUS_READY;
    timer = 3;
}

bool Environment::isBlockVisible(int c, int r)
{
  if(r < 0 || r >= BLOCK_ROWS) return false;
  if(c < 0 || c >= BLOCK_COLUMNS) return false;
  return blocks[r * BLOCK_COLUMNS + c].isVisible();
}

void Environment::initLevel()
{
  for(int y = 0; y < BLOCK_ROWS; y++)
    for(int x = 0; x < BLOCK_COLUMNS; x++)
      blocks[y * BLOCK_COLUMNS + x].init(*this, levels[level][y * BLOCK_COLUMNS + x], x, y);
}

void Environment::nextLevel()
{
  if(level == 9)
  {
    status = STATUS_FINISH;
    return;
  }
  level++;
  lives++;
  initLevel();
  ball.reset();
  ready();
}

void Environment::move(float dt)
{
  if(status == STATUS_GAME_OVER || status == STATUS_FINISH)
  {
    timer -= dt;
    if(timer <= 0)
    if(digitalRead(PIN_LEFT) == LOW || digitalRead(PIN_RIGHT) == LOW)
       startGame(); 
    return;
  }
  if(status == STATUS_READY)
  {
    timer -= dt;
    if(timer <= 0)
    if(digitalRead(PIN_LEFT) == LOW || digitalRead(PIN_RIGHT) == LOW)
       status = STATUS_RUNNING; 
  }  
  for(int i = 0; i < BLOCK_COUNT; i++)
    blocks[i].move(dt);
  if(digitalRead(PIN_LEFT) == LOW)
  {
    if(status == STATUS_START)
      status = STATUS_RUNNING;
    player.left(dt);
  }
  if(digitalRead(PIN_RIGHT) == LOW)
  {
    if(status == STATUS_START)
      status = STATUS_RUNNING;
    player.right(dt);
  }
  if(status == STATUS_RUNNING)
    ball.move(dt);
  for(int i = 0; i < BLOCK_COUNT; i++)
  if(blocks[i].hit(ball.x, ball.y))
  {
    blocks[i].reflect(ball);
    break;
  }
  
  if(ball.status == Ball::STATUS_INACTIVE)
  {
    lives--;
    if(lives == 0)
    {
      status = STATUS_GAME_OVER;
      timer = 3;
    }
    else
    {
      ball.reset();
      ready();
    }
  }
  for(int i = 0; i < BLOCK_COUNT; i++)
    if(!blocks[i].irelevant()) return;
  //still here.. level clear
  nextLevel();
}

void Environment::draw()
{
  if(status == STATUS_GAME_OVER)
  {
    float t = timer > 0 ? timer : 0;
    graphics.setCursor(6, 8 + int(t * 20));
    graphics.println("GAME OVER");
    //if(timer <= 0)
    {
      graphics.setCursor(18, 20 + int(t * 30));
      graphics.print("score");  
      int s = score;
      int p = 0;
      do{
        s /= 10;
        p++;
      }while(s > 0);
      p *= graphics.getFontWidth();
      graphics.setCursor((XRES - p) / 2 + t, 30 + int(t * 40));
      graphics.print(score);  
    }
    return;  
  }
  
  if(status == STATUS_FINISH)
  {
    float t = timer > 0 ? timer : 0;
    graphics.setCursor(8, 8 + int(t * 20));
    graphics.println("YOU WON!");
    //if(timer <= 0)
    {
      graphics.setCursor(18, 20 + int(t * 30));
      graphics.print("score");  
      int s = score;
      int p = 0;
      do{
        s /= 10;
        p++;
      }while(s > 0);
      p *= graphics.getFontWidth();
      graphics.setCursor((XRES - p) / 2 + t, 30 + int(t * 40));
      graphics.print(score);  
    }
    return;  
  }
  
  for(int i = 0; i < lives; i++)
    graphics.pixel(i * 3, YRES - 1, 1, 0);
  for(int i = 0; i < BLOCK_COUNT; i++)
    blocks[i].draw();
  player.draw();
  ball.draw();
  
  if(status == STATUS_READY)
  {
    graphics.rectFill(8, 6, 48, 12, 0, 0);
    graphics.setCursor(11, 8);
    graphics.print("level ");
    graphics.print(level);
    if(timer <= 0)
    {
      graphics.rectFill(8, 18, 48, 12, 0, 0);
      graphics.setCursor(15, 20);
      graphics.println("ready?");
    }
  }  
}

