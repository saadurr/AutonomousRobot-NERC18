/*
Author: Saad Ur Rehman
Email: saad.ur.rehman77@gmail.com
*/

/*

                             _______                      _   _            __               _
                            |__   __|                    | \ | |          / _|             | |
  ______   ______   ______     | | ___  __ _ _ __ ___    |  \| | ___  ___| |_ ___ _ __ __ _| |_ _   _   ______   ______   ______
  |______| |______| |______|    | |/ _ \/ _` | '_ ` _ \   | . ` |/ _ \/ __|  _/ _ \ '__/ _` | __| | | | |______| |______| |______|
                               | |  __/ (_| | | | | | |  | |\  | (_) \__ \ ||  __/ | | (_| | |_| |_| |
                               |_|\___|\__,_|_| |_| |_|  |_| \_|\___/|___/_| \___|_|  \__,_|\__|\__,_|


*/



#include <Servo.h>

Servo shaft;
Servo potter;


unsigned int pwmLeft = 6;
unsigned int pwmRight = 7;
//right motor
unsigned int r1 = 10;
unsigned int r2 = 11;
unsigned int r3 = 12;
unsigned int r4 = 13;
//left motor
unsigned int l1 = 6;
unsigned int l2 = 7;
unsigned int l3 = 8;
unsigned int l4 = 9;

const unsigned char rightEncoderPin = 19;
const unsigned char leftEncoderPin = 18;
void rightEncoderIsr(void);
void leftEncoderIsr(void);

volatile unsigned long pulseRight = 0;
volatile unsigned long pulseLeft = 0;
volatile unsigned long pulse = 0;
/*--------------------------------------------------------
  ----------------------------------------------------------------SENSOR CODE-------------------------------------------------------------------------------------------
  ----------------------------------------------------------------------*/
//Sensor readings
int IRval_left1 = 0;
int IRval_left2 = 0;
int IRval_mid = 0;
int IRval_right1 = 0;
int IRval_right2 = 0;
int IRval = 0;

int colorVal_left = 0;
int colorVal_right = 0;
int colorVal_front = 0;
int colorVal_back = 0;

//Sensor pins
unsigned int out_left1 = A1;
unsigned int out_left2 = A5;
unsigned int out_right1 = A3;
unsigned int out_right2 = A4;
unsigned int out_mid = A2;

//sensor functions
int readIR (int pinNum);
int colorCheckIR(int pinNum);
void readSensors(); //read sensor value each time
void sensorSerialPrint(); //check values on serial comm

int colorDetect();
/*------------------------------------------------------------------------Sensor Code End---------------------------------------------------*/


//movement variables
unsigned int motorSpeed = 50;
unsigned int cwAdjSpeed = 140;
unsigned int ccwAdjSpeed = 140;
unsigned int ccwTicAdjust = 0;
unsigned int cwTicAdjust = 0;

int counter = 0; //for mazemapping

//movement functions
void cw (int, int);
void cw90();
void ccw (int, int);
void ccw90();
void forward(int, int);
void forward(int);
void reverse(int, int);
void fullBrake();
void fullBrake(int); //Brake with delay
void leftEncoderIsr();

void ballPot(int);
void align();
void autoAlign(); //align without tics
void lineFollow();
void mazeMap();
void junctionDetected();

//-------Delay Variables-----

void wait (int); //custom delay
unsigned long millisCurrent = 0;

//-----------------------------------------------------------------SETUP---------------------------------------------------------------------------

void setup() {
  // put your setup code here, to run once:pinMode(r1, OUTPUT);

  Serial.begin(9600);
  pinMode(pwmRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);


  //right motor
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  //left motor
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);

  //  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(leftEncoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(19), leftEncoderIsr, CHANGE);


  //  pinMode(rightEncoderPin, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(18), rightEncoderIsr, CHANGE);

  //IR module readings
  pinMode(out_left1, INPUT);
  pinMode(out_left2, INPUT);
  pinMode(out_right1, INPUT);
  pinMode(out_right2, INPUT);
  pinMode(out_mid, INPUT);

  delay(1000);
}

void loop()
{
  //lineFollow();
  //sensorSerialPrint();
}



/*----------------------------------------------------------------------------------------------------------------------------------

                          _        _____   _   _   ______     ______    ____    _        _         ____   __          __
                         | |      |_   _| | \ | | |  ____|   |  ____|  / __ \  | |      | |       / __ \  \ \        / /
    ______     ______    | |        | |   |  \| | | |__      | |__    | |  | | | |      | |      | |  | |  \ \  /\  / /     ______     ______
   |______|   |______|   | |        | |   | . ` | |  __|     |  __|   | |  | | | |      | |      | |  | |   \ \/  \/ /     |______|   |______|
                         | |____   _| |_  | |\  | | |____    | |      | |__| | | |____  | |____  | |__| |    \  /\  /
                         |______| |_____| |_| \_| |______|   |_|       \____/  |______| |______|  \____/      \/  \/


  Line Follow
  ---------------------------------------------------------------------------------------------------------------------------------- */

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
    cw(30 + cwTicAdjust, cwAdjSpeed);
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
    ccw(180 + ccwTicAdjust, ccwAdjSpeed);
  }
  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // all on color, junction
  {
    return; // do nothing, exit function
  }
}

void lineFollow()
{
  forward(motorSpeed);
  align();
}

void mazeMap()
{
  readSensors();
  if ((  (IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0) ))
  {
    junctionDetected();
  }
  else
    align();
}

void autoAlign()
{
  readSensors();
  //0 is white and not-zero is color

  if ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0)) //straight, when centered
    return;

  //any of the left sensors is on color
  else if (((IRval_left2 == 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
           || ((IRval_left2 != 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
           || ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
           || ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0)))
  {
    while ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
    {
      readSensors();
      cw(10, cwAdjSpeed);
    }
  }

  //any of the right sensors are on color
  else if (((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 == 0))
           || ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 == 0) && (IRval_right2 != 0))
           || ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid == 0) && (IRval_right1 != 0) && (IRval_right2 != 0))
           || ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)))
  {
    while ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
    {
      readSensors();
      ccw(10, ccwAdjSpeed);
    }
  }

  else if ((IRval_left2 != 0) && (IRval_left1 != 0) && (IRval_mid != 0) && (IRval_right1 != 0) && (IRval_right2 != 0)) // all on color, junction
  {
    junctionDetected();
    return;
  }
}

void junctionDetected()
{
  forward(70, 80);
  fullBrake(400);
  counter++;

  /*this part will be used to align the color sensors to read the map, it will move until it senses color on all sensors
     while((colorVal_left==0) && (colorVal_right==0) && (colorVal_front==0)&&(colorVal_back==0))
     {
        readColorSensors();
        forward(10,50);
        align();
     }
  */
  return;
}



/*----------------------------------------------------------------------------------------------------------------------------------

                                   __  __    ____   __      __  ______   __  __   ______   _   _   _______
                                  |  \/  |  / __ \  \ \    / / |  ____| |  \/  | |  ____| | \ | | |__   __|
  ______     ______     ______    | \  / | | |  | |  \ \  / /  | |__    | \  / | | |__    |  \| |    | |       ______     ______     ______
  |______|   |______|   |______|   | |\/| | | |  | |   \ \/ /   |  __|   | |\/| | |  __|   | . ` |    | |      |______|   |______|   |______|
                                  | |  | | | |__| |    \  /    | |____  | |  | | | |____  | |\  |    | |
                                  |_|  |_|  \____/      \/     |______| |_|  |_| |______| |_| \_|    |_|


  Movement Functions
  ----------------------------------------------------------------------------------------------------------------------------------*/
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
  analogWrite(l1, Speed);
  analogWrite(l2, Speed);
  analogWrite(l3, 0);
  analogWrite(l4, 0);

  analogWrite(r1, 0);
  analogWrite(r2, 0);
  analogWrite(r3, Speed);
  analogWrite(r4, Speed);

  while (pulseLeft < tics );
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
  //pulseLeft = 0;
  //pulseRight = 0;
}

void fullBrake(int timer0)
{
  fullBrake();
  delay(timer0);
}

void cw90()
{
  cw(80, 60);

  while ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
  {
    readSensors();
    cw(10, 70);
  }
  fullBrake(200);
  return;
}

void ccw90()
{
  ccw(80, 60);

  while ((IRval_left2 == 0) && (IRval_left1 == 0) && (IRval_mid != 0) && (IRval_right1 == 0) && (IRval_right2 == 0))
  {
    readSensors();
    ccw(10, 70);
  }
  fullBrake(200);
  return;
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

/*------------------------------------------------------------------------------------------------------------------------
                                    _____
                                   / ____|
  ______     ______     ______    | (___     ___   _ __    ___    ___    _ __   ___     ______     ______     ______
  |______|   |______|   |______|    \___ \   / _ \ | '_ \  / __|  / _ \  | '__| / __|   |______|   |______|   |______|
                                   ____) | |  __/ | | | | \__ \ | (_) | | |    \__ \
                                  |_____/   \___| |_| |_| |___/  \___/  |_|    |___/
  Sensor Function
  ---------------------------------------------------------------------------------------------------------------------------*/

void readSensors()
{
  IRval_left1 = colorCheckIR(out_left1);
  IRval_left2 = colorCheckIR(out_left2);
  IRval_mid = colorCheckIR(out_mid);
  IRval_right1 = colorCheckIR(out_right1);
  IRval_right2 = colorCheckIR(out_right2);

  //color sensors reading goes here
  //  0 ---> white
  //  1 ---> black
  //  2 ---> blue
  //  3 ----> red
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
    if (IRval >= 500 && IRval <= 750) //------------------------------------------------ white is 0 //set to 415 if the line sensing is not correct
      return 0;
    else
      return 1;   //--------------------------------------this is color
  }

  if (pin == out_left2) //left 2
  {
    if (IRval >= 500 && IRval <= 740)
      return 0;
    else
      return 1;
  }

  if (pin == out_mid) //mid
  {
    if (IRval >= 420 && IRval <= 625)
      return 0;
    else
      return 1;
  }

  if (pin == out_right1) //right 1
  {
    if (IRval >= 650 && IRval <= 780)
      return 0;
    else
      return 1;
  }

  if (pin == out_right2) //right 2
  {
    if (IRval >= 590 && IRval <= 815)
      return 0;
    else
      return 1;
  }
}

//color sensor function to read values
int colorDetect()
{

}

void sensorSerialPrint()
{
  //  ////--------------------------------------------------------- Left - 1 IR Sensor -------------------------------------------------------
  //    Serial.println("\t \t Left1 value:");                                         //take sensor input
  //    IRval_left1 = readIR(out_left1);
  //
  //    Serial.println(IRval_left1);
  //    delay(200);
  //
  //    if (colorCheckIR(out_left1) == 0)
  //      Serial.println(" White");
  //    else
  //      Serial.println(" Color");
  //
  //    delay(500);
  //
  //
  //  //  ////--------------------------------------------------------- Left - 2 IR Sensor -------------------------------------------------------
  //    Serial.println("\t \t Left2 value");                                         //take sensor input
  //    IRval_left2 = readIR(out_left2);
  //    Serial.println(IRval_left2);
  //    delay(200);
  //    if (colorCheckIR(out_left2) == 0)
  //      Serial.println(" White");
  //    else
  //      Serial.println(" Color");
  //
  //  //    delay(500);
  //
  //  //  //  //////----------------------------------------Middle IR Sensor--------------------------------
  //
  //    Serial.println("\t \t Mid value");                                         //take sensor input
  //    IRval_mid = readIR(out_mid);
  //    Serial.println(IRval_mid);
  //    delay(200);
  //    if (colorCheckIR(out_mid) == 0)
  //      Serial.println(" White");
  //    else
  //      Serial.println(" Color");
  //
  //  //  delay(500);
  //  //
  //  //  ////-------------------------------------------------------------Right - 1 IR Sensor----------------------------------------
  //    Serial.println("\t \t Right1 value : ");
  //    IRval_right1 = readIR(out_right1);
  //    Serial.println(IRval_right1);
  //    delay(200);
  //    if (colorCheckIR(out_right1) == 0)
  //      Serial.println(" White");
  //    else
  //      Serial.println(" Color");
  //
  ////    delay(500);
  //
  //  //  ////-------------------------------------------------------------Right - 2 IR Sensor----------------------------------------
  //    Serial.println("\t \t Right2 value : ");
  //    IRval_right2 = readIR(out_right2);
  //    Serial.println(IRval_right2);
  //    delay(200);
  //
  //    if (colorCheckIR(out_right2) == 0)
  //      Serial.println(" White");
  //    else
  //      Serial.println(" Color");
  //    delay(500);
}


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

void ballPot(int dir)
{
  shaft.attach(3);
  potter.attach(2);

  //initial position
  shaft.writeMicroseconds(1300);
  potter.writeMicroseconds(1000);
  delay(2000);


  potter.writeMicroseconds(1800);
  delay(500);
  potter.writeMicroseconds(1650);
  delay(500);
  potter.writeMicroseconds(1400);
  delay(500);

  //dir 1 for cw
  //dir 0 for mid
  //dir 2 for ccw
  if (dir == 0)
  {
    shaft.write(70);
  }
  else if (dir == 1)
  {
    shaft.write(0);
  }

  else if (dir == 2)
  {
    shaft.write(170);
  }

  else
    return;

  delay(1500);

  potter.writeMicroseconds(200);
  delay(1000);


  //return to mean position after potting the ball
  shaft.writeMicroseconds(1300);
  potter.writeMicroseconds(1000);

  //detach the ports to avoid interference
  shaft.detach();
  potter.detach();
}

// --------------------------------------------------------------------Custom Delay------------------------------------------------------------------ -
void wait(int period)
{
  millisCurrent = millis();

  while (millis() < millisCurrent + period);
}


