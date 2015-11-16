//Concepts of Engineering Arduino Demo
//Justin A. Barnes
//ENGR1402-002

//Analog input pins for accelerometer
const int xPin = 0; //pin Analog 0 (A0)
const int yPin = 1; //pin Analog 1 (A1)
const int zPin = 2; //pin Analog 2 (A2)

//LED Pins
const int redPin = 3;
const int greenPin = 9;
const int bluePin = 10;

//digital input Pins
const int potPin = 3; //pin Analog 3 (A3)
const int selectorPin = 2;
const int durationPin = 4;
const int resetPin = 5;
int resetState = 1;
int selectedPin = redPin;
int selectorState = 1;

//default values
int potValue = 0; //start from 255 as common anode, TF turned off
const int potLow = 4;
const int potHigh = 820;
int accLow = 271;
int accHigh = 405;
int xValue = 0;
int yValue = 0;
int zValue = 0;
int pwmValue = 0;
int analogReadPin = potPin;

void setup() {  
  Serial.begin(9600);
  //Since we are using analogWrite on this pin, setting it to output is not needed
  //pinMode(bluePin,OUTPUT);
}

void loop() {
  selectorState = digitalRead(selectorPin);
  if(selectorState == LOW) 
  {
    //switch LEDs
    if (selectedPin == redPin)
      selectedPin = greenPin;
    else if (selectedPin == greenPin)
      selectedPin = bluePin;
    else
      selectedPin = redPin;

    delay(500);
  }

  resetState = digitalRead(resetPin);
  if (resetState == LOW)
  {
    if (analogReadPin == potPin)
      analogReadPin = zPin;
    else
      analogReadPin = potPin;

    delay(500);
  }

  pwmValue = analogRead(analogReadPin);

  if (analogReadPin == potPin)
  {
    potValue = map(pwmValue,potLow,potHigh,0,255);
    analogWrite(selectedPin,potValue);
  }
  else
  {
    zValue = map(pwmValue,accLow,accHigh,0,255);
    analogWrite(selectedPin,zValue);
  }
  
  //Serial.print("Button State:  ");
  //Serial.println(selectorState);
  //Serial.println(potValue);
  // delay(200);

  //  if (zValue < accLow)
  //    accLow = zValue;
  //
  //  if (zValue > accHigh)
  //    accHigh = zValue;

    Serial.print("Raw Pot:   ");
    Serial.print(analogRead(potPin));
    Serial.print("  accLow:  ");
    Serial.print(potLow);
    Serial.print("  accHigh:  ");
    Serial.print(potHigh);
    Serial.print("  pwm Value:  ");
    Serial.println(potValue);
 
}
