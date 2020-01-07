
int readValueFromPin(const int& pin) {
  return analogRead(pin);
}

float toVoltage(int val) {
  return val * (5.0f/1023.0f);
}

int mapSensorToRGBValue(const int sensorValue) {
  return map(sensorValue, 0, 1023, 0, 255);
}
