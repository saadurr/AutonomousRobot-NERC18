
#include "globalConfig.h"



void junctionDetected()
{
  forward(junctionForward, 80); //jf,60
  fullBrake(junctionDelay);

  if (counterRead == 1)
  {
    counter++;
    if (counter == 2)
    {
      motorSpeed = 90;
      forward(180, 80); //250, 60
      fullBrake(10); //edit
      for (int i = 0; i < 20; i++)
      {
        forward(7, 100); //5,100
        ccw(30, 160); //19,140
        if (i > 18) //17
          center();
      }
    }

    else if (counter == 3)
    {
      motorSpeed = 90;
      cw(40, 100);
      forward(50, 70);
      for (int i = 0; i < 15; i++) //20
      {
        forward(30, 200); //25, 160
        center();
      }
    }
    else if (counter == 4)
    {
      forward(650, 90); //730
      fullBrake(100);
      if (decideBridge == 1) //out ball
      {
        //        forward(300, 100);
        fullBrake(10);
        cw(650, 160);
        fullBrake(10);
        ballPot(0);
        ccw(500, 140);
        forward(100, 120);
        center();
        //---------------------
        //        cw(220, 130);
        //        fullBrake(100);
        //        forward(130, 100);
        //        ballPot(1);
        //        center();
        //        ccw(100, 120);
      }
      else if (decideBridge == 0) //inward ball
      {
        //        ccw(130, 120);
        //        fullBrake(100);
        //        forward(315, 100);
        //        ballPot(2);
        //        center();
        //        cw(100, 120);
        //----------------------------
        fullBrake(10);
        center();
        ccw(550, 120); //600,140
        fullBrake(10);
        forward(180, 100);
        ballPot(0);
        cw(400, 160); //400,140
        forward(50, 120);
        center();
      }

      forward(60, 100);
      //      motorSpeed = 55;
      for (int i = 0; i < 50; i++) //50
      {
        forward(10, 160); //10,140
        fullBrake(5); //5
        center();
      }
      ccwAdjSpeed = 165; //155
      cwAdjSpeed = 165; //160
      junctionForward = 150;
      counter = 6;//edit 009
    }

    else if (counter >= 6)
    {
      ccw(60, 120); //edit 0: 40
      startMillis = millis();
      motorSpeed = 90;
      while (1)
      {
        currentMillis = millis();
        if (currentMillis - startMillis >= 2500)
        {
          cwAdjSpeed = 200;
          ccwAdjSpeed = 200;
        }
        if (currentMillis - startMillis >= period)
        {
          break;
        }
        forward(motorSpeed); //previous 90
        center();
      }
      while (1)
      {
        readSensors();

        if (IRval_left1 != 0 && IRval_right2 != 0)
        {
          fullBrake(400);
          reverse(150, 70);
          ccw(20, 120);
          forward(100, 70);
          cw(80, 120);
          forward(165, 50); //160
          cw(520, 120); //510
          center();
          ballPot(0);
          success = 1;
          return;
        }

        forward(motorSpeed - 15); //60
        center();
      }
      return;
    }
  }


  if (flag_localize == 1)
  {
    if ((local_point >= 2 && local_point <= 4) || local_point == 9 || local_point == 8)
      local_counter--;
    else if ((local_point >= 5 && local_point <= 7) || local_point == 0 || local_point == 1)
      local_counter++;
  }


  if (flag_localizeEnd == 1)
  {
    counterRead = 1;
    ccw90();
    counter = 0;
    flag_localizeEnd = -1;
  }

  else if (flag_localizeEnd == 2)
  {
    counterRead = 1;
    ccw90();
    counter = 1;
    flag_localizeEnd = -1;
  }

  return;
}
