#include "Keyboard.h"

// From https://gamefaqs.gamespot.com/snes/916396-super-nintendo/faqs/5395
//       ----------------------------- ---------------------
//      |                             |                      \
//      | (1)     (2)     (3)     (4) |  (X)     (X)      (7) |
//      |                             |                      /
//       ----------------------------- ---------------------
//
//
//        Pin     Description             Color of wire in cable
//        ===     ===========             ======================
//        1       +5v                     White
//        2       Data clock              Yellow
//        3       Data latch              Orange
//        4       Serial data             Red
//        7       Ground                  Brown

// These are the arduino pins, not the snes pins from above
#define CLOCK_PIN 7
#define DATA_PIN 6
#define LATCH_PIN 5

// Store the buttons in a single 16-bit number
uint16_t previousButtons = 0;

/* 
    +----------+---------------+
    |   Button | Bit Position  |
    +----------+---------------+
    |     B    |      0        |
    |     Y    |      1        |
    |  Select  |      2        |
    |   Start  |      3        |
    |    Up    |      4        |
    |   Down   |      5        |
    |   Left   |      6        |
    |  Right   |      7        |
    |     A    |      8        |
    |     X    |      9        |
    |     L    |     10        |
    |     R    |     11        |
    +----------+---------------+
*/

// This is the default button map for the openEmu emulator
int buttonMap[] = {'s', 'a', KEY_RIGHT_SHIFT, KEY_RETURN,
                  KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW,
                  KEY_RIGHT_ARROW, 'd', 'w', 'e', 'q' };

void setup() {
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);

  digitalWrite(CLOCK_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
  
  pinMode(DATA_PIN, OUTPUT);
  digitalWrite(DATA_PIN, HIGH);
  
  pinMode(DATA_PIN, INPUT); 

  Keyboard.begin();
}

void loop() {
  // Tell the controller to latch the inputs
  digitalWrite(LATCH_PIN, HIGH);
  delayMicroseconds(12);
  digitalWrite(LATCH_PIN, LOW);
  delayMicroseconds(6);

  uint16_t currentButtons = 0;

  for (int i = 0; i < 16; i++) {
    digitalWrite(CLOCK_PIN, LOW);
    delayMicroseconds(6);
    currentButtons |= digitalRead(DATA_PIN) << i;
    delayMicroseconds(6);
    digitalWrite(CLOCK_PIN, HIGH);
  }

  // Iterate the keys and send press/release events for changes.
  // As per the key diagram above, we only care about the first 12 bits
  for (int i = 0; i <= 11; i++) {
    auto now = ((currentButtons & (1 << i)) >> i);
    auto prev = ((previousButtons & (1 << i)) >> i);

    // Press
    if (now == 1 && prev == 0) {
      Keyboard.press(buttonMap[i]);
    } else {
      // Release
      if (now == 0 && prev == 1) {
        Keyboard.release(buttonMap[i]);
      }
    }
  }

  previousButtons = currentButtons;

  delay(16);
}
