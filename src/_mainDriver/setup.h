
//-----------------------------------------------------------------SETUP---------------------------------------------------------------------------
#include "globalConfig.h"

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


  pinMode(rightEncoderPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(18), rightEncoderIsr, CHANGE);

  //IR module readings
  pinMode(out_left1, INPUT);
  pinMode(out_left2, INPUT);
  pinMode(out_right1, INPUT);
  pinMode(out_right2, INPUT);
  pinMode(out_mid, INPUT);
  pinMode(bridgeSignal, INPUT);

  //Ultrasonic Module Readings
  pinMode(front_triggerPin, OUTPUT);
  pinMode(front_echoPin, INPUT);
  pinMode(right_triggerPin, OUTPUT);
  pinMode(right_echoPin, INPUT);
  pinMode(left_triggerPin, OUTPUT);
  pinMode(left_echoPin, INPUT);
  pinMode(back_triggerPin, OUTPUT);
  pinMode(back_echoPin, INPUT);

  decideBridge = digitalRead(bridgeSignal);
  conflictJunction = digitalRead(decideJunction);
 
  delay(500);
}

