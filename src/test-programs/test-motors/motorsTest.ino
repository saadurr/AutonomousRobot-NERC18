/*
Author: Saad Ur Rehman
Email: saad.ur.rehman77@gmail.com
*/

//-----------------------------------------------------------Motor Test----------------------------------------------------------------------
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

unsigned int SpeedLeft = 0;
unsigned int SpeedRight = 0;

//Encoders
void rightEncoderIsr(void);
void leftEncoderIsr(void);

volatile unsigned long pulseRight = 0;
volatile unsigned long pulseLeft = 0;
volatile unsigned long pulse = 0;

void cw (int, int);
void ccw (int, int);
void forward(int, int);
void forward(int);
void reverse(int, int);
void fullBrake();
void fullBrake(int); //Brake with delay
void leftEncoderIsr();

//----------------------------------------------------------------------------Setup-------------------------------------------------------
void setup() {
  // put your setup code here, to run once:pinMode(r1, OUTPUT);
  Serial.begin(9600);

  shaft.attach(3);
  potter.attach(2);

  shaft.writeMicroseconds(1300);
  potter.writeMicroseconds(1000);
  
  pinMode(pwmRight, OUTPUT);
  pinMode(pwmLeft, OUTPUT);

  //right motor
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);

  //left motorr
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);


  pinMode(leftEncoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(19), leftEncoderIsr, FALLING);

  //  pinMode(rightEncoderPin, INPUT_PULLUP);
  //  attachInterrupt(digitalPinToInterrupt(18), rightEncoderIsr, CHANGE);

  delay(1000);
}

//-----------------------------------------------------------------------loop--------------------------------------------------------------

void loop()
{
//   potter.writeMicroseconds(1800);
//    delay(500);
//  potter.writeMicroseconds(1650);
//    delay(500);
//  potter.writeMicroseconds(1400);
//    delay(500);
//  potter.writeMicroseconds(200);
//  delay(500);
//forward(100);
shaft.writeMicroseconds(700);
}

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

////---------------------------------------------------------------------- Encoder Tics Funtions
void rightEncoderIsr()
{
  //SpeedRight=(1000000/(micros()-prevTimeRight));
  pulseRight++;
  //prevTimeRight=micros();
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
