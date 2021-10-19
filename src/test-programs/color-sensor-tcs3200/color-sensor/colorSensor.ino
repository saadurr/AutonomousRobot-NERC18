/*
Author: Saad Ur Rehman
Email: saad.ur.rehman77@gmail.com
*/

unsigned int front_sensorOut = A14;
unsigned int front_S2 = A9;
unsigned int front_S3 = A10;

unsigned int left_sensorOut = A13;
unsigned int left_S2 = A12;
unsigned int left_S3 = A11;

unsigned int right_sensorOut = A15; 
unsigned int right_S2 = A8;
unsigned int right_S3 = A7;

int frequency = 0;

void setup() {
  pinMode(front_S2, OUTPUT);
  pinMode(front_S3, OUTPUT);
  pinMode(front_sensorOut, INPUT);

  pinMode(right_S2, OUTPUT);
  pinMode(right_S3, OUTPUT);
  pinMode(right_sensorOut, INPUT);

  pinMode(left_S2, OUTPUT);
  pinMode(left_S3, OUTPUT);
  pinMode(left_sensorOut, INPUT);

  Serial.begin(9600);
}

void loop() {

  // Setting red filtered photodiodes to be read
 

  
  Serial.println("Right: ");
  digitalWrite(right_S2, LOW);
  digitalWrite(right_S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(right_sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");

  // Setting Green filtered photodiodes to be read
  digitalWrite(right_S2, HIGH);
  digitalWrite(right_S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(right_sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");

  // Setting Blue filtered photodiodes to be read
  digitalWrite(right_S2, LOW);
  digitalWrite(right_S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(right_sensorOut, LOW);
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");


}
