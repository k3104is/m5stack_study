#include "public.h"
// the setup routine runs once when M5Stack starts up
void setup(){

  // Initialize the M5Stack object
  M5.begin();

  // LCD display
  M5.Lcd.print("Hello World");

  BT_setup();
}

// the loop routine runs over and over again forever
void loop() {
  BT_loop();
}
