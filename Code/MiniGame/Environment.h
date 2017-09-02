/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#pragma once
#include "Ball.h"
#include "Paddle.h"
#include "Sound.h"
#include "Graphics.h"

class Environment
{
  public:
  int XRES;
  int YRES;
  Ball ball;
  Paddle player;
  Sound& sound;
  Graphics& graphics;
  int status;
  const int STATUS_START = 0;
  const int STATUS_RUNNING = 1;
  const int STATUS_GAME_OVER = 2;
  const int STATUS_INTRO = 3;
  const int STATUS_READY = 4;
  const int STATUS_FINISH = 5;

  const int PIN_LEFT = D3;
  const int PIN_RIGHT = D6;
  
  int score;
  int level;
  int lives;
  float timer;
  Environment(Graphics& g, Sound& s);
  void startGame();
  void initLevel();
  void nextLevel();
  void ready();
  bool isBlockVisible(int c, int r);
  void move(float dt);
  void draw();
};

