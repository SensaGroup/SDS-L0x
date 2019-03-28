#include <Arduino.h>

#include "motor.h"
#include "sensor.h"
#include "hall.h"
#include "can.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.println("L0X starting up...");

  Serial.print("Setting up motor...");
  motor_init();
  Serial.println("done");

  Serial.print("Setting up hall...");
  hall_setup();
  Serial.println("done");

  /*Serial.print("Setting up sensors...");
  if(!sensor_init()) {
    Serial.println("not inited... halting...");
    while(1);
  } 
  Serial.println("done");
  */

 Serial.print("Setting up can...");
 if(can_init(CAN_250KBPS) == false) {
   while(1);
 }
 Serial.println("done");

  motor_stop();
}

void loop() {
  
}
