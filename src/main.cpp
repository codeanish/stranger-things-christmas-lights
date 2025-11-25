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
  pinMode(clearPin, OUTPUT);

  digitalWrite(clearPin, LOW);
  delay(50);
  digitalWrite(clearPin, HIGH);

  Serial.println("Setup complete");
  delay(2000);
}

constexpr uint32_t letterPatterns[26] = {
  /* A */ 0b00000000000000000000000000000001UL,
  /* B */ 0b00000000000000000000000000000010UL,
  /* C */ 0b00000000000000000000000000000100UL,
  /* D */ 0b00000000000000000000000000001000UL,
  /* E */ 0b00000000000000000000000000010000UL,
  /* F */ 0b00000000000000000000000000100000UL,
  /* G */ 0b00000000000000000000000001000000UL,
  /* H */ 0b00000000000000000000000010000000UL,
  /* I */ 0b00000000000000000000000100000000UL,
  /* J */ 0b00000000000000000000001000000000UL,
  /* K */ 0b00000000000000000000010000000000UL,
  /* L */ 0b00000000000000000000100000000000UL,
  /* M */ 0b00000000000000000001000000000000UL,
  /* N */ 0b00000000000000000010000000000000UL,
  /* O */ 0b00000000000000000100000000000000UL,
  /* P */ 0b00000000000000001000000000000000UL,
  /* Q */ 0b00000000000000010000000000000000UL,
  /* R */ 0b00000000000000100000000000000000UL,
  /* S */ 0b00000000000001000000000000000000UL,
  /* T */ 0b00000000000010000000000000000000UL,
  /* U */ 0b00000000000100000000000000000000UL,
  /* V */ 0b00000000001000000000000000000000UL,
  /* W */ 0b00000000010000000000000000000000UL,
  /* X */ 0b00000000100000000000000000000000UL,
  /* Y */ 0b00000001000000000000000000000000UL,
  /* Z */ 0b00000010000000000000000000000000UL   // LED 26 = last output
};

#define letter(c)  letterPatterns[(c) - 'A']

void send32bits(uint32_t data) {
  digitalWrite(latchClock, LOW);
  shiftOut(serialData, shiftClock, MSBFIRST, (data >> 24) & 0xFF);  // 4th register
  shiftOut(serialData, shiftClock, MSBFIRST, (data >> 16) & 0xFF);  // 3rd
  shiftOut(serialData, shiftClock, MSBFIRST, (data >>  8) & 0xFF);  // 2nd
  shiftOut(serialData, shiftClock, MSBFIRST,  data        & 0xFF);  // 1st register
  digitalWrite(latchClock, HIGH);
}

String message = "MERRY CHRISTMAS!";

void loop() {
  for (int i = 0; i < message.length(); i++) {
    char c = message[i];
    if (c == ' '){
      continue;
    }
    if (c == '!'){
      for(int i = 0; i < 10; i++){
        send32bits(0xFFFFFFFF);
        delay(100);
        send32bits(0);
        delay(100);
      }
    }
    else {
      send32bits(letter(c));
      delay(2000);
    }
    send32bits(0);
    delay(500);
  }

  send32bits(0);
  delay(2000);
}