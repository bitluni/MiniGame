/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#pragma once
class Environment;

class Ball
{
  public:
  float x, y;
  float vx, vy;
  float speed;
  const float RADIUS = 1.5f;
  int status;
  static const int STATUS_INACTIVE = 0;
  static const int STATUS_ACTIVE = 1;
  Environment& environment;
  Ball(Environment& e);
  Ball(Environment& e, float startX, float startY, float startVx, float startVy);
  void normalize();
  void reset();
  void draw();
  void move(float dt);
};
