
/*------------------------------------------------------------------------------------------------------------------------
                                    _____
                                   / ____|
  ______     ______     ______    | (___     ___   _ __    ___    ___    _ __   ___     ______     ______     ______
 |______|   |______|   |______|    \___ \   / _ \ | '_ \  / __|  / _ \  | '__| / __|   |______|   |______|   |______|
                                   ____) | |  __/ | | | | \__ \ | (_) | | |    \__ \
                                  |_____/   \___| |_| |_| |___/  \___/  |_|    |___/
  Sensor Function
  ---------------------------------------------------------------------------------------------------------------------------*/

#include "globalConfig.h"



void readSensors()
{
  IRval_left1 = colorCheckIR(out_left1);
  IRval_left2 = colorCheckIR(out_left2);
  IRval_mid = colorCheckIR(out_mid);
  IRval_right1 = colorCheckIR(out_right1);
  IRval_right2 = colorCheckIR(out_right2);
}


int readIR (int pinNum)
{
  return analogRead(pinNum);
}

int colorCheckIR(int pin)
{
  IRval = 0;
  for (int i = 0; i < 5; i++)
  {
    IRval += readIR(pin);
  }
  IRval = IRval / 5;

  if (pin == out_left1) //left 1
  {
    if (IRval >= 450 && IRval <= 635) //------------------------------------------------ white is 0 //set to 415 if the line sensing is not correct
      return 0;
    else
      return 1;   //--------------------------------------this is color
  }

  if (pin == out_left2) //left 2
  {
    if (IRval >= 600 && IRval <= 760)
      return 0;
    else
      return 1;
  }

  if (pin == out_mid) //mid
  {
    if (IRval >= 430 && IRval <= 600)
      return 0;
    else
      return 1;
  }

  if (pin == out_right1) //right 1
  {
    if (IRval >= 620 && IRval <= 830)
      return 0;
    else
      return 1;
  }

  if (pin == out_right2) //right 2
  {
    if (IRval >= 580 && IRval <= 850)
      return 0;
    else
      return 1;
  }
}


void readSonar()
{
  digitalWrite(front_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(front_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(front_triggerPin, LOW);
  sonar_duration = pulseIn(front_echoPin, HIGH);
  distance_front = sonar_duration * 0.034 / 2;

  digitalWrite(back_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(back_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(back_triggerPin, LOW);
  sonar_duration = pulseIn(back_echoPin, HIGH);
  distance_back = sonar_duration * 0.034 / 2;

  digitalWrite(left_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(left_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(left_triggerPin, LOW);
  sonar_duration = pulseIn(left_echoPin, HIGH);
  distance_left = sonar_duration * 0.034 / 2;

  digitalWrite(right_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(right_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(right_triggerPin, LOW);
  sonar_duration = pulseIn(right_echoPin, HIGH);
  distance_right = sonar_duration * 0.034 / 2;
}


