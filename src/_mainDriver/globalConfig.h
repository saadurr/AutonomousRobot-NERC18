/*

                             _______                      _   _            __               _
                            |__   __|                    | \ | |          / _|             | |
  ______   ______   ______     | | ___  __ _ _ __ ___    |  \| | ___  ___| |_ ___ _ __ __ _| |_ _   _   ______   ______   ______
  |______| |______| |______|    | |/ _ \/ _` | '_ ` _ \   | . ` |/ _ \/ __|  _/ _ \ '__/ _` | __| | | | |______| |______| |______|
                               | |  __/ (_| | | | | | |  | |\  | (_) \__ \ ||  __/ | | (_| | |_| |_| |
                               |_|\___|\__,_|_| |_| |_|  |_| \_|\___/|___/_| \___|_|  \__,_|\__|\__,_|


*/


//--------------------------------------------------------- Saad Ur Rehman-------------------------------------------------------------------
//--------------------------------------------------------- Module - Localization -------------------------------------------------------------

#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H

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

//----Ultrasonic
const int front_triggerPin = 51;
const int front_echoPin = 28;
const int left_triggerPin = 53;
const int left_echoPin = 22;
const int right_triggerPin = 47;
const int right_echoPin = 26;
const int back_triggerPin = 49;
const int back_echoPin = 24;
unsigned int distance_front = 0;
unsigned int distance_back = 0;
unsigned int distance_left = 0;
unsigned int distance_right = 0;
long sonar_duration = 0;
void readSonar();
/*------------------------------------------------------------------------Sensor Code End---------------------------------------------------*/


//movement variables
unsigned int motorSpeed = 90; //90
unsigned int motorSpeed_pot = 60; //70
unsigned int cwAdjSpeed = 150;
unsigned int ccwAdjSpeed = 80;
unsigned int ccwTicAdjust = 0;
unsigned int cwTicAdjust = 25;
unsigned int junctionDelay = 0;
unsigned int junctionForward = 80; //80

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
void center();
void autoAlign(); //align without tics
void lineFollow();
void junctionDetected();

//-----localization functions & variable
void nosferatu();
void localize();
void mapping();
void explore(unsigned int, unsigned int);
void setOrientation(unsigned int, unsigned int);
unsigned int local_position = -1;
unsigned int local_orientation = -1;
unsigned int local_counter = 0;
unsigned int local_point = -1;
unsigned int flag_localize = 0;
unsigned int flag_localizeEnd = -1;
unsigned int counterRead = -1;
unsigned int firstRun = 1;
unsigned int localizeSuccess = -1;
unsigned int success = -1;
unsigned int distance_temp = 0;
unsigned int bridgeSignal = 32; //pin number
unsigned int decideBridge = -1;
unsigned int conflictJunction = -1; //1 for 7, 0 for 2
unsigned int decideJunction = 30; //pin number
//-------Delay Variables-----

unsigned long startMillis = 0;
unsigned long currentMillis = 0;
const unsigned long period = 6500; 

//--------temp functions for alignment-----
void softAlign();
void hardAlign();

#endif
