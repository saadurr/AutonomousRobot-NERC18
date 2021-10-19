/*
Author: Saad Ur Rehman
Email: saad.ur.rehman77@gmail.com
*/

/*--------------------------------------------------------
  ----------------------------------------------------------------IR SENSOR CODE-------------------------------------------------------------------------------------------
  ----------------------------------------------------------------------*/

//Sensor readings
int freq_left1 = 0;
int freq_left2 = 0;
int freq_mid = 0;
int freq_right1 = 0;
int freq_right2 = 0;


int freq = 0;

//Sensor pins
unsigned int out_left1 = A1;
unsigned int out_left2 = A5;
unsigned int out_right1 = A3;
unsigned int out_right2 = A4;
unsigned int out_mid = A2;


//sensor functions
int readIR (int pinNum);
int colorCheck(int pinNum);

void setup()
{
  Serial.begin(9600);

  pinMode(out_left1, INPUT);
  pinMode(out_left2, INPUT);
  pinMode(out_right1, INPUT);
  pinMode(out_right2, INPUT);
  pinMode(out_mid, INPUT);

}

void loop ()
{ //  ////--------------------------------------------------------- Left - 1 IR Sensor -------------------------------------------------------
  Serial.println("\t \t Left1 value:");                                         //take sensor input
  freq_left1 = readIR(out_left1);

  Serial.println(freq_left1);
  delay(500);
  //
  if (colorCheck(out_left1) == 0)
    Serial.println(" White");
  else
    Serial.println(" Color");
  //  //////
  //  ////  delay(500);
  //  //
  //  //
  //  //  //  //  ////--------------------------------------------------------- Left - 2 IR Sensor -------------------------------------------------------
  Serial.println("\t \t Left2 value");                                         //take sensor input
  freq_left2 = readIR(out_left2);
  Serial.println(freq_left2);
  delay(500);
  //
  if (colorCheck(out_left2) == 0)
    Serial.println(" White");
  else
    Serial.println(" Color");
  //  //
  //  //  //    delay(500);
  //  //
  //  ////  //  //  //////----------------------------------------Middle IR Sensor--------------------------------
  //  //  ////  //
  Serial.println("\t \t Mid value");                                         //take sensor input
  freq_mid = readIR(out_mid);

  Serial.println(freq_mid);
  delay(200);
  //
  if (colorCheck(out_mid) == 0)
    Serial.println(" White");
  else
    Serial.println(" Color");

  //  //    delay(500);
  //  //  //
  //  //  ////  //  ////-------------------------------------------------------------Right - 1 IR Sensor----------------------------------------
  //  //  //  //
  Serial.println("\t \t Right1 value : ");
  freq_right1 = readIR(out_right1);
  Serial.println(freq_right1);
  delay(500);

  if (colorCheck(out_right1) == 0)
    Serial.println(" White");
  else
    Serial.println(" Color");
  //  //  //
  //  //  //    delay(500);
  //  //  ////
  //  //  ////  //  ////-------------------------------------------------------------Right - 2 IR Sensor----------------------------------------
  //  ////  //
  Serial.println("\t \t Right2 value : ");
  freq_right2 = readIR(out_right2);
  Serial.println(freq_right2);
  delay(500);
  //
  if (colorCheck(out_right2) == 0)
    Serial.println(" White");
  else
    Serial.println(" Color");
  //
  //  //    delay(500);


}


int readIR (int pinNum)
{
  return analogRead(pinNum);
}

int colorCheck(int pin)
{
  freq = readIR(pin);

  if (pin == out_left1) //left 1
  {
    if (freq >= 450 && freq <= 605) //------------------------------------------------ white is 0
      return 0;
    else
      return 1;   //--------------------------------------this is color
  }

  if (pin == out_left2) //left 2
  {
    if (freq >= 600 && freq <= 760)
    {
      return 0;
    }
    else
      return 1;
  }

  if (pin == out_mid) //mid
  {
    if (freq >= 435 && freq <= 580)
      return 0;
    else
      return 1;
  }

  if (pin == out_right1) //right 1
  {
    if (freq >= 630 && freq <= 830)
      return 0;
    else
      return 1;
  }

  if (pin == out_right2) //right 2
  {
    if (freq >= 580 && freq <= 850)
      return 0;
    else
      return 1;
  }
}
