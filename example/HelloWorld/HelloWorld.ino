#include "LCI2C.h"

LC_I2C display(39, 16, 2);

void setup(){
  Serial.begin(9600);
  display.init();
}

void loop() {
  display.set_position_cursor(0, 0);
  display.print("Hello");
  display.set_position_cursor(0, 1);
  display.print("World !");
  delay(500);
  ldisplaycd.clear();

}
