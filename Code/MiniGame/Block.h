/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#pragma once
class Environment;
#include "Ball.h"

class Block
{
  public:
  int x, y;
  static const int WIDTH = 8;
  static const int HEIGHT = 3;
  int type;
  float timer;
  static const int TYPE_GONE = 0;
  static const int TYPE_BASIC = 1;
  static const int TYPE_SOLID = 2;
  static const int TYPE_HARD1 = 3;
  static const int TYPE_HARD2 = 4;
  static const int TYPE_SPAWN10 = 5;
  static const int TYPE_SPAWN11 = 6;
  static const int TYPE_SPAWN20 = 7;
  static const int TYPE_SPAWN21 = 8;
  static const int TYPE_SPAWN22 = 9;
  static const int SPAWN_TIME = 3;
  Environment* environment;
  Block();
  void init(Environment& e, int type, int x, int y);
  void degrade();
  bool destroy();
  bool hit(float bx, float by);
  void reflect(Ball& b);
  void draw();
  void move(float dt);
  bool isVisible();
  bool irelevant();
};

