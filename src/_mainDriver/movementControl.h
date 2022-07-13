
/*----------------------------------------------------------------------------------------------------------------------------------

                                   __  __    ____   __      __  ______   __  __   ______   _   _   _______
                                  |  \/  |  / __ \  \ \    / / |  ____| |  \/  | |  ____| | \ | | |__   __|
  ______     ______     ______    | \  / | | |  | |  \ \  / /  | |__    | \  / | | |__    |  \| |    | |       ______     ______     ______
 |______|   |______|   |______|   | |\/| | | |  | |   \ \/ /   |  __|   | |\/| | |  __|   | . ` |    | |      |______|   |______|   |______|
                                  | |  | | | |__| |    \  /    | |____  | |  | | | |____  | |\  |    | |
                                  |_|  |_|  \____/      \/     |______| |_|  |_| |______| |_| \_|    |_|


  Movement Functions
  ----------------------------------------------------------------------------------------------------------------------------------*/

#include "globalConfig.h"


void reverse(int Speed)
{
  pulseLeft = 0;
  pulseRight = 0;
  analogWrite(l1, 0);
  analogWrite(l2, 0);
  analogWrite(l3, Speed);
  analogWrite(l4, Speed);

  analogWrite(r1, 0);
  analogWrite(r2, 0);
  analogWrite(r3, Speed);
  analogWrite(r4, Speed);
}

void reverse(int tics , int Speed)
{
  pulseLeft = 0;
  pulseRight = 0;
  analogWrite(l1, 0);
  analogWrite(l2, 0);
  analogWrite(l3, Speed);
  analogWrite(l4, Speed);

  analogWrite(r1, 0);
  analogWrite(r2, 0);
  analogWrite(r3, Speed);
  analogWrite(r4, Speed);

  while (pulseLeft <= tics);
  fullBrake();
  delay(5);
}

void cw(int tics, int Speed)
{
  pulseLeft = 0;
  pulseRight = 0;
  analogWrite(l1, Speed);
  analogWrite(l2, Speed);
  analogWrite(l3, 0);
  analogWrite(l4, 0);

  analogWrite(r1, 0);
  analogWrite(r2, 0);
  analogWrite(r3, Speed);
  analogWrite(r4, Speed);

  while (pulseRight < tics );
  fullBrake();
}

void ccw(int tics, int Speed)
{
  pulseLeft = 0;
  pulseRight = 0;
  analogWrite(l1, 0);
  analogWrite(l2, 0);
  analogWrite(l3, Speed);
  analogWrite(l4, Speed);

  analogWrite(r1, Speed);
  analogWrite(r2, Speed);
  analogWrite(r3, 0);
  analogWrite(r4, 0);
  while (pulseLeft < tics);
  fullBrake();
}

void forward(int tics , int Speed)
{
  pulseLeft = 0;
  pulseRight = 0;
  analogWrite(l1, Speed);
  analogWrite(l2, Speed);
  analogWrite(l3, 0);
  analogWrite(l4, 0);

  analogWrite(r1, Speed);
  analogWrite(r2, Speed);
  analogWrite(r3, 0);
  analogWrite(r4, 0);
  while (pulseLeft <= tics);

  fullBrake();
}
void forward(int Speed)
{
  pulseLeft = 0;
  pulseRight = 0;

  analogWrite(l1, Speed);
  analogWrite(l2, Speed);
  analogWrite(l3, 0);
  analogWrite(l4, 0);

  analogWrite(r1, Speed);
  analogWrite(r2, Speed);
  analogWrite(r3, 0);
  analogWrite(r4, 0);
}

//------------Complete Brake
void fullBrake()
{
  analogWrite(l1, 255);
  analogWrite(l2, 0);
  analogWrite(l3, 0);
  analogWrite(l4, 255);

  analogWrite(r1, 255);
  analogWrite(r2, 0);
  analogWrite(r3, 0);
  analogWrite(r4, 255);
}

void fullBrake(int timer0)
{
  fullBrake();
  delay(timer0);
}

void cw90()
{
  cw(400, 140); //300
  readSensors();
  while (1)
  {
    readSensors();
    if (IRval_left2 == 0 && IRval_mid != 0 && IRval_right2 == 0)
      break;
    cw(15, 200); //edit 0: 25,200
  }
  center();
  fullBrake(100);
//  center();
}

void ccw90()
{
  fullBrake(10); //edit
  ccw(400, 120);
  fullBrake(10); //edit
  readSensors();
  while (1)
  {
    if (IRval_left2 == 0 && IRval_mid != 0 && IRval_right2 == 0)
      break;
    readSensors();
    ccw(10, 140); //edit 0: 10, 140
  }
  center();
  fullBrake(100);
//  center();
}


////---------------------------------------------------------------------- Encoder Tics Funtions-------------------------------------------------
void rightEncoderIsr()
{
  pulseRight++;
  //  Serial.print("Right Encoder :");
  //  Serial.println(pulseRight);
}
void leftEncoderIsr()
{
  pulseLeft++;
  //  pulse++;
  //  Serial.print("Left Encoder :");
  //  Serial.println(pulseLeft);
}

