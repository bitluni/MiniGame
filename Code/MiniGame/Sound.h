/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#pragma once
class Sound
{
  public:
  int pin;
  int freq;
  int duration;
  int offTime;
  int newTone;
  
  Sound(int pin);
  void beep(int beep, int duration);
  void process(int t);
};
