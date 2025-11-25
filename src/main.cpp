#include <Arduino.h>

const int serialData = 25;
const int shiftClock = 27;
const int latchClock = 26;
const int clearPin = 33;

void setup() {
  Serial.begin(115200);
  pinMode(serialData, OUTPUT);
  pinMode(shiftClock, OUTPUT);
  pinMode(latchClock, OUTPUT);
  pinMode(clearPin, OUTPUT);  // Add this!

  digitalWrite(clearPin, LOW);
  delay(50);  // Brief pulse for clear
  digitalWrite(clearPin, HIGH);

  Serial.println("Setup complete");
  delay(2000);
}

int datArray[] = {B00000000, B10000000, B01000000, B00100000, B00010000, B00001000, B00000100, B00000010, B00000001};

void loop() {
  for(int value = 0; value < 9; value++) {
    digitalWrite(latchClock, LOW);
    Serial.println(datArray[value], BIN);
    shiftOut(serialData, shiftClock, LSBFIRST, datArray[value]);
    shiftOut(serialData, shiftClock, LSBFIRST, datArray[value]);
    shiftOut(serialData, shiftClock, LSBFIRST, datArray[value]);
    shiftOut(serialData, shiftClock, LSBFIRST, datArray[value]);
    digitalWrite(latchClock, HIGH);
    delay(2000);
  }
}