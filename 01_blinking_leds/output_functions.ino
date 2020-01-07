void osicillate(int& val){
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
  
  feedToOutputPINs(osicillateCounter);
}

void feed(String& led, int& val, int& outpin) {
  analogWrite(outpin, val);
  printToSerialMonitor(led, val, outpin);
}

void feedToOutputPINs(int& val) {
  
  for (int i = 0; i != totalOutPINs; ++i) {
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

void fadeLED() {
  osicillate(sensorValue);
}

void normalLED() {
  feedToOutputPINs(sensorValue);
}
