//Concepts of Engineering Arduino Demo
//Justin A. Barnes
//ENGR1402-002

//Analog input pins for accelerometer
const int xPin = 0; //pin Analog 0 (A0)
const int yPin = 1; //pin Analog 1 (A1)
const int zPin = 2; //pin Analog 2 (A2)

//Analog input pin for potentiometer
const int potPin = 3; //pin Analog 3 (A3)

//LED Pins
const int redPin = 3;
const int greenPin = 9;
const int bluePin = 10;

//digital input Pins
const int selectorPin = 2; //yellow button
const int holdPin = 4;     //blue butotn
int holdState = 1;
const int resetPin = 5;    //black button
int resetState = 1;
int selectedPin = redPin;
int selectorState = 1;

//default values
int potValue = 0; //start from 255 as common anode, TF turned off
const int potLow = 4;    //These potentiometer values are derived by using a pot
const int potHigh = 820; //as a voltage divider and finding the low and high values
int accLow = 415;        //These accelerometer values are derived by rotating about
int accHigh = 615;       //the Z-axis to find the low and high output.
int xValue = 0;
int yValue = 0;          //Initially, set all these to off.
int zValue = 0;
int analogValue =0;
int pwmValue = 0;
int analogReadPin = zPin; //Start with accelerometer z pin as input control

void setup() {  
  analogReference(EXTERNAL);
  Serial.begin(9600);
  //Since we are using analogWrite on this pin, setting it to output is not needed
  //pinMode(bluePin,OUTPUT);
}

void loop() {
  selectorState = digitalRead(selectorPin);
  if(selectorState == LOW) 
  {
    //Switch LEDs
    if (selectedPin == redPin)
      selectedPin = greenPin;
    else if (selectedPin == greenPin)
      selectedPin = bluePin;
    else
      selectedPin = redPin;

    delay(500);
  }

  //This portion holds the current color.
  //To unlock the hold, press the black button again.
  holdState = digitalRead(holdPin);
  if(holdState == LOW)
  {
    delay(500);
    do
    {
      holdState=digitalRead(holdPin);
    } while(holdState == HIGH);
    delay(500);
  }

  //Read & map analog values to PWM values
  analogValue = analogRead(analogReadPin);

  if (analogReadPin == potPin)
  {
    pwmValue = map(analogValue,potLow,potHigh,0,255);
  }
  else if(analogReadPin == zPin)
  {
    pwmValue = map(analogValue,accLow,accHigh,0,255);
  }

  //Roughly filter out overflow values on the PWM output
  if(pwmValue < 0)
    pwmValue = 0;
  if(pwmValue > 255)
    pwmValue = 255;

  analogWrite(selectedPin,pwmValue);

  Serial.print("Raw zPin:   ");
  Serial.print(analogRead(zPin));
  Serial.print("  accLow:  ");
  Serial.print(accLow);
  Serial.print("  accHigh:  ");
  Serial.print(accHigh);
  Serial.print("  pwm Value:  ");
  Serial.println(pwmValue);
 
}
