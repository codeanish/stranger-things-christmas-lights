#include <Arduino.h>

const int serialData = 25;
const int shiftClock = 26;
const int latchClock = 27;
const int clearPin = 33;

void setup() {
  Serial.begin(115200);
  pinMode(serialData, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(clearPin, OUTPUT);  // Add this!

  // Clear the shift register, then return SRCLR to HIGH (normal operation)
  digitalWrite(clearPin, LOW);
  delay(10);  // Brief pulse for clear
  digitalWrite(clearPin, HIGH);

  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, MSBFIRST, B1111111);
  digitalWrite(latchClock, HIGH);

  Serial.println("Setup complete");
  delay(2000);
}

int datArray[] = {B00000000, B10000000, B11000000, B11100000, B11110000, B11111000, B11111100, B11111110, B11111111};

void loop() {
  for(int value = 0; value < 9; value++) {
    digitalWrite(latchClock, LOW);
    Serial.println(datArray[value], BIN);
    shiftOut(serialData, shiftClock, MSBFIRST, datArray[value]);
    digitalWrite(latchClock, HIGH);
    delay(2000);
  }
}