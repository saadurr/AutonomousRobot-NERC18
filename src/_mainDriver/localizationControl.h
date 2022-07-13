/*
                                 _                     _ _          _   _
                                | |                   | (_)        | | (_)
      ______   ______   ______  | |     ___   ___ __ _| |_ ______ _| |_ _  ___  _ __    ______   ______   ______
     |______| |______| |______| | |    / _ \ / __/ _` | | |_  / _` | __| |/ _ \| '_ \  |______| |______| |______|
                                | |___| (_) | (_| (_| | | |/ / (_| | |_| | (_) | | | |
                                |______\___/ \___\__,_|_|_/___\__,_|\__|_|\___/|_| |_|
*/

#include "globalConfig.h"



void nosferatu()
{
  if (firstRun == 1)
  {
    localize();
    firstRun = -1;
  }
  if (localizeSuccess == 1)
  {
    lineFollow();
  }
  if (success == 1)
  {
    localizeSuccess = 2;
    fullBrake(10000);
    fullBrake(10000);
  }
}

void localize()
{
  mapping();
  explore(local_position, local_orientation);
  return;
}

void mapping()
{
  while (1)
  {
    readSonar();
    //        Serial.println(distance_front);
    //        Serial.println(distance_back);
    //        Serial.println(distance_left);
    //        Serial.println(distance_right);

    if ((distance_front > 200 && distance_front < 220) && (distance_back > 24 && distance_back < 44)
        && (distance_left > 25 && distance_left < 45) && (distance_right > 110 && distance_right < 130))
    {
      local_position = 0;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 110 && distance_front < 130) && (distance_back > 20 && distance_back < 40)
             && (distance_left > 197 && distance_left < 217) && (distance_right > 23 && distance_right < 43))
    {

      local_position = 0;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 21 && distance_front < 41) && (distance_back > 198 && distance_back < 218)
             && (distance_left > 110 && distance_left < 130) && (distance_right > 23 && distance_right < 43))
    {
      local_position = 0;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 18 && distance_front < 38) && (distance_back > 116 && distance_back < 136)
             && (distance_left > 24 && distance_left < 44) && (distance_right > 199 && distance_right < 219))
    {
      local_position = 0;
      local_orientation = 3;
      break;
    }


    else if ((distance_front > 154 && distance_front < 174) && (distance_back > 65 && distance_back < 85)
             && (distance_left > 26 && distance_left < 46) && (distance_right > 106 && distance_right < 126))
    {
      local_position = 1;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 109 && distance_front < 129) && (distance_back > 21 && distance_back < 41)
             && (distance_left > 154 && distance_left < 174) && (distance_right > 66 && distance_right < 86))
    {
      local_position = 1;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 66 && distance_front < 86) && (distance_back > 152 && distance_back < 172)
             && (distance_left > 108 && distance_left < 128) && (distance_right > 23 && distance_right < 43))
    {
      local_position = 1;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 23 && distance_front < 43) && (distance_back > 107 && distance_back < 127)
             && (distance_left > 66 && distance_left < 86) && (distance_right > 153 && distance_right < 173))
    {
      local_position = 1;
      local_orientation = 3;
      break;
    }

    else if ((distance_front > 110 && distance_front < 130) && (distance_back > 110 && distance_back < 130)
             && (distance_left > 25 && distance_left < 45) && (distance_right > 64 && distance_right < 84) && (conflictJunction == 0))
    {
      local_position = 2;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 66 && distance_front < 86) && (distance_back > 22 && distance_back < 42)
             && (distance_left > 109 && distance_left < 129) && (distance_right > 107 && distance_right < 127) && (conflictJunction == 0))
    {
      local_position = 2;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 110 && distance_front < 130 ) && (distance_back > 108  && distance_back < 128 )
             && (distance_left > 66  && distance_left < 86 ) && (distance_right > 24  && distance_right < 44 ) && (conflictJunction == 0))
    {
      local_position = 2;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 19 && distance_front < 39) && (distance_back > 68 && distance_back < 88)
             && (distance_left > 110 && distance_left < 130) && (distance_right > 109 && distance_right < 129) && (conflictJunction == 0))
    {
      local_position = 2;
      local_orientation = 3;
      break;
    }


    else if ((distance_front > 65 && distance_front < 85) && (distance_back > 153 && distance_back < 173)
             && (distance_left > 26 && distance_left < 46) && (distance_right > 63 && distance_right < 83))
    {
      local_position = 3;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 66 && distance_front < 86) && (distance_back > 23 && distance_back < 43)
             && (distance_left > 64 && distance_left < 84) && (distance_right > 155 && distance_right < 175)) //(distance_right > 57 && distance_right < 77)
    {
      local_position = 3;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 156 && distance_front < 176) && (distance_back > 62 && distance_back < 82)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 25 && distance_right < 45))
    {
      local_position = 3;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 21 && distance_front < 41) && (distance_back > 65 && distance_back < 85)
             && (distance_left > 155 && distance_left < 175) && (distance_right > 64 && distance_right < 84))
    {
      local_position = 3;
      local_orientation = 3;
      break;
    }


    else if ((distance_front > 22 && distance_front < 42) && (distance_back > 85 && distance_back < 105)
             && (distance_left > 25 && distance_left < 45) && (distance_right > 58 && distance_right < 78))
    {
      local_position = 4;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 66 && distance_front < 86) && (distance_back > 22 && distance_back < 42)
             && (distance_left > 22 && distance_left < 42) && (distance_right > 85 && distance_right < 105))
    {
      local_position = 4;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 85 && distance_front < 105) && (distance_back > 23 && distance_back < 43)
             && (distance_left > 64 && distance_left < 84) && (distance_right > 25 && distance_right < 45))
    {
      local_position = 4;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 20 && distance_front < 40) && (distance_back > 66 && distance_back < 86)
             && (distance_left > 88 && distance_left < 108) && (distance_right > 21 && distance_right < 41))
    {
      local_position = 4;
      local_orientation = 3;
      break;
    }

    else if ((distance_front > 22 && distance_front < 42) && (distance_back > 87 && distance_back < 107)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 24 && distance_right < 84))
    {
      local_position = 5;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 23 && distance_front < 43) && (distance_back > 63 && distance_back < 83)
             && (distance_left > 21 && distance_left < 41) && (distance_right > 90 && distance_right < 115))
    {
      local_position = 5;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 89 && distance_front < 109) && (distance_back > 20 && distance_back < 40)
             && (distance_left > 25 && distance_left < 45) && (distance_right > 66 && distance_right < 86))
    {
      local_position = 5;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 67 && distance_front < 87) && (distance_back > 22 && distance_back < 42)
             && (distance_left > 86 && distance_left < 106) && (distance_right > 21 && distance_right < 41))
    {
      local_position = 5;
      local_orientation = 3;
      break;
    }


    else if ((distance_front > 66 && distance_front < 86) && (distance_back > 151 && distance_back < 171)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 24 && distance_right < 44))
    {
      local_position = 6;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 23 && distance_front < 43) && (distance_back > 63 && distance_back < 83)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 153 && distance_right < 173))
    {
      local_position = 6;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 156 && distance_front < 176) && (distance_back > 63 && distance_back < 83)
             && (distance_left > 25 && distance_left < 45) && (distance_right > 65 && distance_right < 85))
    {
      local_position = 6;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 68 && distance_front < 88) && (distance_back > 22 && distance_back < 42)
             && (distance_left > 153 && distance_left < 173) && (distance_right > 65 && distance_right < 85))
    {
      local_position = 6;
      local_orientation = 3;
      break;
    }

    else if ((distance_front > 111 && distance_front < 131) && (distance_back > 107 && distance_back < 127)
             && (distance_left > 66 && distance_left < 86) && (distance_right > 23 && distance_right < 43) && (conflictJunction == 1))
    {
      local_position = 7;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 25 && distance_front < 45) && (distance_back > 63 && distance_back < 83)
             && (distance_left > 108 && distance_left < 128) && (distance_right > 109 && distance_right < 129) && (conflictJunction == 1))
    {
      local_position = 7;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 111 && distance_front < 131) && (distance_back > 107 && distance_back < 127)
             && (distance_left > 64 && distance_left < 84) && (distance_right > 66 && distance_right < 86) && (conflictJunction == 1))
    {
      local_position = 7;
      local_orientation = 2;
      break;
    }

    else if ((distance_front > 68 && distance_front < 88) && (distance_back > 65 && distance_back < 85)
             && (distance_left > 109 && distance_left < 129) && (distance_right > 109 && distance_right < 129) && (conflictJunction == 1))
    {
      local_position = 7;
      local_orientation = 3;
      break;
    }


    else if ((distance_front > 155 && distance_front < 175) && (distance_back > 64 && distance_back < 84)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 66 && distance_right < 86))
    {
      local_position = 8;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 68 && distance_front < 88) && (distance_back > 63 && distance_back < 83)
             && (distance_left > 151 && distance_left < 171) && (distance_right > 65 && distance_right < 85))
    {
      local_position = 8;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 63 && distance_front < 83) && (distance_back > 155 && distance_back < 175)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 66 && distance_right < 86))
    {
      local_position = 8;
      local_orientation = 2;
      break;
    }

    else if ((distance_front >= 67 && distance_front <= 87) && (distance_back >= 64 && distance_back <= 84)
             && (distance_left >= 65 && distance_left <= 85) && (distance_right >= 155 && distance_right <= 176))
    {
      local_position = 8;
      local_orientation = 3;
      break;
    }


    else if ((distance_front >= 199 && distance_front <= 219) && (distance_back >= 22 && distance_back <= 42)
             && (distance_left >= 65 && distance_left <= 85) && (distance_right >= 65 && distance_right <= 85))
    {
      local_position = 9;
      local_orientation = 0;
      break;
    }

    else if ((distance_front > 65 && distance_front < 85) && (distance_back > 66 && distance_back < 86)
             && (distance_left > 199 && distance_left < 218) && (distance_right > 23 && distance_right < 43))
    {
      local_position = 9;
      local_orientation = 1;
      break;
    }

    else if ((distance_front > 23 && distance_front < 43) && (distance_back > 200 && distance_back < 220)
             && (distance_left > 65 && distance_left < 85) && (distance_right > 65 && distance_right < 85))
    {
      local_position = 9;
      local_orientation = 2;
      break;
    }

    else  if ((distance_front > 67 && distance_front < 87) && (distance_back > 65 && distance_back < 85)
              && (distance_left > 23 && distance_left < 43) && (distance_right > 200 && distance_right < 218))
    {
      local_position = 9;
      local_orientation = 3;
      break;
    }
  }

  //  Serial.println(local_position);
  //  Serial.println(local_orientation);
}

void explore(unsigned int pos, unsigned int orientation)
{

  local_counter = pos;
  local_point = pos;

  if (pos == 0 || pos == 9 || pos == 1 || pos == 8)
  {
    setOrientation(orientation, 0);
  }

  else if (pos >= 2 && pos <= 7)
  {
    setOrientation(orientation, 2);
  }
  flag_localize = 1;

  if (pos >= 2 && pos <= 4)
  {
    while (1)
    {
      lineFollow();
      if (local_counter == 2 )
        break;
    }
    while (1)
    {
      readSonar();
      forward(motorSpeed_pot);
      center();
      if (distance_left <= 15) //10
      {
        forward(70, 70); //70,70
        fullBrake(10);
        center();
        break;
      }
    }
    ballPot(2);
    flag_localizeEnd = 1;
    localizeSuccess = 1;
    return;
  }

  else if (pos >= 5 && pos <= 7)
  {
    while (1)
    {
      lineFollow();
      if (local_counter == 7)
        break;
    }
    while (1)
    {
      readSonar();
      forward(motorSpeed_pot);
      center();
      if (distance_right <= 15) //10
      {
        forward(60, 70); //70,70
        fullBrake(10);
        center();
        break;
      }
    }
    ballPot(1);
    flag_localizeEnd = 2;
    localizeSuccess = 1;
    return;
  }

  else if (pos == 0 || pos == 1)
  {
    while (1)
    {
      lineFollow();
      if (local_counter == 1)
        break;
    }

    while (1)
    {
      readSonar();
      forward(motorSpeed_pot);
      center();
      if (distance_right <= 15) //10
      {
        forward(70, 70);
        fullBrake(10);
        center();
        cw(20, 120);
        break;
      }
    }
    ballPot(1);
    forward(80, 60);
    ccw90();
    flag_localizeEnd = 1;
    localizeSuccess = 1;
  }

  else if (pos == 9 || pos == 8)
  {
    while (1)
    {
      lineFollow();
      if (local_counter == 8)
        break;
    }
    while (1)
    {
      readSonar();
      forward(motorSpeed_pot);
      center();
      if (distance_left <= 15) //15
      {
        forward(100, 70);
        fullBrake(10);
        center();
        break;
      }
    }
    ballPot(2);
    forward(80, 60);
    cw90(); //180 turn
    flag_localizeEnd = 2;
    localizeSuccess = 1;
    return;
  }

  flag_localize = 0;
  return;
}


void setOrientation(unsigned int current, unsigned int next)
{
  while (current < next)
  {
    current++;
    cw90();
    fullBrake(10);
  }

  while (current > next)
  {
    current--;
    ccw90();
    fullBrake(10);
  }
}
