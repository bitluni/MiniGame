/* 
 * bitluni 2017
 * license cc-by (creative commons attribution)
 * You can use the code freely as long you attribute me
 * https://youtube.com/bitlunislab
 */
#include <Arduino.h>
#include "Sound.h"

Sound::Sound(int pin)
{
  this->pin = pin;
  offTime = 0;
}

void Sound::beep(int freq, int duration)
{
  newTone = freq;
  this->duration = duration;
}

void Sound::process(int t)
{
  if(newTone)
  {
    offTime = t + duration;
    tone(pin, newTone, duration);
    newTone = 0;
  }
  else
  if(t > offTime)
    noTone(pin);
}
  
