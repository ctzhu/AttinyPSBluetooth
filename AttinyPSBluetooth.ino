#include "PS2Keyboard.h"
#include "Bluetooth.h"

#define KEYBOARD_CLOCK PB2
#define KEYBOARD_DATA PB0

#define _DEBUG 0

#if _DEBUG
#define HARDWARE_SERIAL_RATE 38400
#else
#define HARDWARE_SERIAL_RATE 115200
#endif

PS2Keyboard keyboard(KEYBOARD_CLOCK, KEYBOARD_DATA);

Bluetooth bluetooth(HARDWARE_SERIAL_RATE, PB4);

/*
1 PB5 
3 PB4
2 PB3 Dont use due to 1.5k pull up
7 PB2
6 PB1 Buildin LED
5 PB0
*/

void setup()
{
bool kbStatus = keyboard.init();
pinMode(1, OUTPUT);
bool keyboardStatus = keyboard.init();
digitalWrite(1, HIGH);
delay(500);
digitalWrite(1, LOW);
delay(500);
#if _DEBUG
  if (keyboardStatus)
    Serial.println("Keyboard detected!");
  else
    Serial.println("No keyboard detected.");
#endif

}

void loop()
{
  if (keyboard.available())
  {
    bluetooth.sendKeyboardState(keyboard.getKeyModifiers(), keyboard.getKeysPressed());
  }
}
