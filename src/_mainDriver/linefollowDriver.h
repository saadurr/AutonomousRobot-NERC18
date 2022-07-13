

/*----------------------------------------------------------------------------------------------------------------------------------

                          _        _____   _   _   ______     ______    ____    _        _         ____   __          __
                         | |      |_   _| | \ | | |  ____|   |  ____|  / __ \  | |      | |       / __ \  \ \        / /
    ______     ______    | |        | |   |  \| | | |__      | |__    | |  | | | |      | |      | |  | |  \ \  /\  / /     ______     ______
   |______|   |______|   | |        | |   | . ` | |  __|     |  __|   | |  | | | |      | |      | |  | |   \ \/  \/ /     |______|   |______|
                         | |____   _| |_  | |\  | | |____    | |      | |__| | | |____  | |____  | |__| |    \  /\  /
                         |______| |_____| |_| \_| |______|   |_|       \____/  |______| |______|  \____/      \/  \/


  Line Follow
  ---------------------------------------------------------------------------------------------------------------------------------- */

#include "globalConfig.h"



void lineFollow()
{
  forward(motorSpeed);
  softAlign();
//    align();
}

void align()
{
  readSensors();
  //0 is white and not-zero is color

  if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //straight, when centered
    return;

  else if ((IRval_left2 == 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //left1 is on color, turn slightly clockwise
  {
    cw(10 + cwTicAdjust, cwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) // left2 and left1 on color, turn ccw
  {
    cw(20 + cwTicAdjust, cwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //left2 is on color, turn more clockwise
  {
    cw(50 + cwTicAdjust, cwAdjSpeed);
  }

  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 == 0)) //right1 is on color, turn slightly counter-clockwise
  {
    ccw(10 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // right2 and right1 on color, turn ccw
  {
    ccw(18 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 != 0)) // right2 is on color, turn more ccw
  {
    ccw(75 + ccwTicAdjust, ccwAdjSpeed);
  }

  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) //right three sensors on colour
  {
    ccw(260 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // all on color, junction
  {
    junctionDetected();
    return; // do nothing, exit function
  }
}

void center()
{
  readSensors();
  //0 is white and not-zero is color

  if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //straight, when centered
    return;

  else if ((IRval_left2 == 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //left1 is on color, turn slightly clockwise
  {
    cw(10 + cwTicAdjust, cwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) // left2 and left1 on color, turn ccw
  {
    cw(20 + cwTicAdjust, cwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //left2 is on color, turn more clockwise
  {
    cw(50 + cwTicAdjust, cwAdjSpeed);
  }

  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 == 0)) //right1 is on color, turn slightly counter-clockwise
  {
    ccw(10 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // right2 and right1 on color, turn ccw
  {
    ccw(18 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 != 0)) // right2 is on color, turn more ccw
  {
    ccw(75 + ccwTicAdjust, ccwAdjSpeed);
  }

  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) //right three sensors on colour
  {
    ccw(80 + ccwTicAdjust, ccwAdjSpeed); //130
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //edit0009
    {
      cw(80 + cwTicAdjust, cwAdjSpeed);
    }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // all on color, junction
  {
    return; // do nothing, exit function
  }
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------

void softAlign()
{
  readSensors();
  //0 is white and not-zero is color

  if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //straight, when centered
    return;

  else if ((IRval_left2 == 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //left1 is on color, turn slightly clockwise
  {
    cw(5 + cwTicAdjust, cwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) // left2 and left1 on color, turn ccw
  {
    cw(10 + cwTicAdjust, cwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //left2 is on color, turn more clockwise
  {
    cw(25 + cwTicAdjust, cwAdjSpeed);
  }

  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 == 0)) //right1 is on color, turn slightly counter-clockwise
  {
    ccw(5 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // right2 and right1 on color, turn ccw
  {
    ccw(9 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 != 0)) // right2 is on color, turn more ccw
  {
    ccw(37 + ccwTicAdjust, ccwAdjSpeed);
  }

  else if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) //right three sensors on colour
  {
    ccw(130 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // all on color, junction
  {
    junctionDetected();
    return; // do nothing, exit function
  }
}


