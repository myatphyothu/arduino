/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer:
      - connected to analog pin A0.
      - Center pin of the potentiometer goes to A0.
      - side pins of the potentiometer go to +5V and GND
  - LED connected from digital pin 9 to ground
  - button
      - attached to pin 2 and +5V
  -10K resistor attached to pin 2 and GND

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe


*/

// These constants won't change. They're used to give names to the pins used:
const int potentiometerInPIN = A0;  // Analog input pin that the potentiometer is attached to
const int buttonInPIN = 2;
const int analogOutPin = 9; // Analog output pin that the LED is attached to

bool FADE_MODE = true;
bool BTN_PRESSED = false;
bool high = false;
bool low = true;
int btnPressTime = 0;
int timeToWaitBeforeNextPress = 500; // 500ms

float deltaTime = 0.0f;

//int[] outPINs = new int[]{9};
int outPINs[] = {9,10,11};
int totalOutPINs = sizeof(outPINs) / sizeof(*outPINs);
int osicillateTimer = 255;
int osicillateCounter = 0;
int osicillateIncrement = 1;

int rawSensorValue = 0;
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)

bool incrementPhase = true;

void setup_InputsAndOutputs(){
  pinMode(buttonInPIN, INPUT);
  for (int i = 0; i != totalOutPINs; ++i){
    pinMode(outPINs[i], OUTPUT);
  }
}

void setup() {
  
  setup_InputsAndOutputs();
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  rawSensorValue = readValueFromPin(potentiometerInPIN);
  sensorValue = mapSensorToRGBValue(rawSensorValue);
  registerBtnPress();
  //Serial.print(pushBtnState + "\n");
  FADE_MODE = BTN_PRESSED;
  //Serial.print(FADE_MODE + "\n");
  if (FADE_MODE)
    fadeLED();
  else
    normalLED();
  delay(2);
}
