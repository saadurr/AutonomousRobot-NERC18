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
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

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

  //  //Front Color Sensor
  //  Serial.println("\nFront: ");
  //  digitalWrite(front_S2, LOW);
  //  digitalWrite(front_S3, LOW);
  //  // Reading the output frequency
  //  frequency = pulseIn(front_sensorOut, LOW);
  //  frequency = map(frequency, 25, 72, 255, 0);
  //  Serial.print("R= ");//printing name
  //  Serial.print(frequency);//printing RED color frequency
  //  Serial.print("  ");
  //
  //  digitalWrite(front_S2, HIGH);
  //  digitalWrite(front_S3, HIGH);
  //  // Reading the output frequency
  //  frequency = pulseIn(front_sensorOut, LOW);
  //  frequency = map(frequency, 25, 72, 255, 0);
  //  // Printing the value on the serial monitor
  //  Serial.print("G= ");//printing name
  //  Serial.print(frequency);//printing RED color frequency
  //  Serial.print("  ");
  //
  //  digitalWrite(front_S2, LOW);
  //  digitalWrite(front_S3, HIGH);
  //  // Reading the output frequency
  //  frequency = pulseIn(front_sensorOut, LOW);
  //  frequency = map(frequency, 25, 72, 255, 0);
  //  // Printing the value on the serial monitor
  //  Serial.print("B= ");//printing name
  //  Serial.print(frequency);//printing RED color frequency
  //  Serial.println("  ");
  //
  //
  //Left Color Sensor
    Serial.println("Left: ");
    digitalWrite(left_S2, LOW);
    digitalWrite(left_S3, LOW);
    // Reading the output frequency
    frequency = pulseIn(left_sensorOut, LOW);
    redColor = map(frequency, 29, 36, 255, 0);
    // Printing the value on the serial monitor
    Serial.print("R= ");//printing name
    Serial.print(frequency);//printing RED color frequency
    Serial.print("  ");
  
    digitalWrite(left_S2, HIGH);
    digitalWrite(left_S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(left_sensorOut, LOW);
    greenColor = map(frequency, 100, 199, 255, 0);
    // Printing the value on the serial monitor
    Serial.print("G= ");//printing name
    Serial.print(frequency);//printing Green
    Serial.print("  ");
  
    digitalWrite(left_S2, LOW);
    digitalWrite(left_S3, HIGH);
    // Reading the output frequency
    frequency = pulseIn(left_sensorOut, LOW);
    blueColor = map(frequency, 173, 180, 255, 0);
    // Printing the value on the serial monitor
    Serial.print("B= ");//printing name
    Serial.print(frequency);//printing Blue
    Serial.println("  ");

  //Right Color Sensor
//  Serial.println("Right: ");
//  digitalWrite(right_S2, LOW);
//  digitalWrite(right_S3, LOW);
//  // Reading the output frequency
//  frequency = pulseIn(right_sensorOut, LOW);
//  redColor = map(frequency, 6, 28, 255, 0);
//  // Printing the value on the serial monitor
//  Serial.print("R= ");//printing name
//  Serial.print(frequency);//printing RED color frequency
//  Serial.print("  ");
//
//  digitalWrite(right_S2, HIGH);
//  digitalWrite(right_S3, HIGH);
//  // Reading the output frequency
//  frequency = pulseIn(right_sensorOut, LOW);
//  greenColor = map(frequency, 100, 199, 255, 0);
//  // Printing the value on the serial monitor
//  Serial.print("G= ");//printing name
//  Serial.print(frequency);//printing Green
//  Serial.print("  ");
//
//  digitalWrite(right_S2, LOW);
//  digitalWrite(right_S3, HIGH);
//  // Reading the output frequency
//  frequency = pulseIn(right_sensorOut, LOW);
//  blueColor = map(frequency, 1, 6, 255, 0);
//  // Printing the value on the serial monitor
//  Serial.print("B= ");//printing name
//  Serial.print(frequency);//printing Blue
//  Serial.println("  ");


  if (redColor > greenColor && redColor > blueColor) {
    Serial.println(" - RED detected!");
  }
//  if (greenColor > redColor && greenColor > blueColor) {
//    Serial.println(" - GREEN detected!");
//  }
 else if (blueColor > redColor && blueColor > greenColor) {
    Serial.println(" - BLUE detected!");
  }
}
