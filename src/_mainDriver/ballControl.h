
/*-------------------------------------------------------------------------------------------------


                    ____        _ _    _____      _   _   _
                   |  _ \      | | |  |  __ \    | | | | (_)
  ______   ______  | |_) | __ _| | |  | |__) |__ | |_| |_ _ _ __   __ _   ______   ______
 |______| |______| |  _ < / _` | | |  |  ___/ _ \| __| __| | '_ \ / _` | |______| |______|
                   | |_) | (_| | | |  | |  | (_) | |_| |_| | | | | (_| |
                   |____/ \__,_|_|_|  |_|   \___/ \__|\__|_|_| |_|\__, |
                                                                   __/ |
                                                                  |___/

  Ball Potting Function
  ---------------------------------------------------------------------------------------------------*/

#include "globalConfig.h"


void ballPot(int dir)
{
  shaft.attach(3);
  potter.attach(4);

  //initial position
  shaft.writeMicroseconds(1300);
  delay(200);
  potter.writeMicroseconds(1000);
  delay(200);

  potter.writeMicroseconds(1800);
  delay(200);
  potter.writeMicroseconds(1650);
  delay(200);
  potter.writeMicroseconds(1400);
  delay(200);

  //dir 1 for cw
  //dir 0 for mid
  //dir 2 for ccw
  if (dir == 0)
  {
    shaft.writeMicroseconds(1100); //1200
    delay(200);
  }
  else if (dir == 1)
  {
    shaft.writeMicroseconds(200);
    delay(200);
  }

  else if (dir == 2)
  {
    //        shaft.write(170);
    shaft.writeMicroseconds(2000);
    delay(200);
  }

  else
    return;

  for (int pos = 120; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    potter.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
  }
  delay(700);

//  potter.writeMicroseconds(0);//back to 200
//  delay(500);
//  potter.writeMicroseconds(0);
//  delay(500);


  //return to mean position after potting the ball
  shaft.writeMicroseconds(1300);
  delay(200);
  potter.writeMicroseconds(1000);
  delay(200);

  //detach the ports to avoid interference
  shaft.detach();
  potter.detach();
}

// --------------------------------------------------------------------Custom Delay------------------------------------------------------------------ -


