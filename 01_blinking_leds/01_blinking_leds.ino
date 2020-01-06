/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInOutSerial
*/

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 9; // Analog output pin that the LED is attached to

float deltaTime = 0.0f;

//int[] outPINs = new int[]{9};
int outPINs[] = {9,10,11};
int osicillateTimer = 255;
int osicillateCounter = 0;
int osicillateIncrement = 1;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

bool incrementPhase = true;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

int readValueFromPin(const int& pin) {
  return analogRead(pin);
}

int mapSensorValue(int sensorValue) {
  return map(sensorValue, 0, 1023, 0, 255);
}

int mapOsicillateValue(float osicillateValue) {
  return map(osicillateValue, 0, osicillateTimer, 0, 255);
}

int getMappedSensorValue(const int& pin) {
  return map(analogRead(pin), 0, 1023, 0, 255);
}

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
 return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void osicillateFeed(int& val){
  if (incrementPhase) {
    if (osicillateCounter < val) {
      osicillateCounter += osicillateIncrement;
      delay(10);
    } else {
      incrementPhase = false;
      delay(100  );
    }
  }else{
    if (osicillateCounter > 0) {
      osicillateCounter -= osicillateIncrement;
      delay(10);
    } else {
      incrementPhase = true;
      delay(100);
    }
  }
  
  //int mappedSensorValue = mapfloat(val,0,osicillateTimer,0,255);
  
  Serial.print(osicillateCounter);
  Serial.print("\n");
  //Serial.print(mappedSensorValue);
  //Serial.print("\n");
  feedToOutputPINs(osicillateCounter);
}

void feed(String& led, int& val, int& outpin) {
  analogWrite(outpin, val);
  printToSerialMonitor(led, val, outpin);
}

void feedToOutputPINs(int& val) {
  
  int t = sizeof(outPINs) / sizeof(*outPINs);
  for (int i = 0; i != t; ++i) {
    String led = "led"+i;
    feed(led, val, *(outPINs+i));
    
  }
}

void printToSerialMonitor(String& led, int& in, int& out){
  /*Serial.print("Led = " + led);
  Serial.print("\tsensor = ");
  Serial.print(in);
  Serial.print("\t output = ");
  Serial.println(out);*/
  
}



void loop() {
  int rawSensorValue = readValueFromPin(analogInPin);
  sensorValue = getMappedSensorValue(analogInPin);
  if (rawSensorValue > 100) {
    
    osicillateFeed(sensorValue);
  } else {
    
    
    feedToOutputPINs(sensorValue);
  }
  delay(2);
}
