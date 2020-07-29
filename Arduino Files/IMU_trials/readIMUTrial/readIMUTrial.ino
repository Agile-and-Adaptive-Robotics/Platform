/*
 * Author: Jake Chung
 * Date: 07/28/2020
 * This program tests the functionality of the IMU
 * FX0S8700+FXAS21002
 * https://www.adafruit.com/product/3463?gclid=CjwKCAjwmf_4BRABEiwAGhDfSVq9WMy_YFl69_LorOhw9kOGppvX7tOEMP-L-8nXFIfrvhOw9mDLchoCOckQAvD_BwE
 */

#include <Adafruit_FXAS21002C.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

//assign unique ID to sensor
Adafruit_FXAS21002C gyro = Adafruit_FXAS21002C(0x0021002C);

void setup() {
  Serial.begin(115200);

  //Wait for the Serial Monitor 
  while (!Serial) {
    delay(1);
  }
  gyro.begin();
}

void loop() {
  //get sensor event
  sensors_event_t event;
  gyro.getEvent(&event);

  Serial.print("Gyro X: ");
  Serial.print(event.gyro.x);
  Serial.print("\t");
  Serial.print("Gyro Y: ");
  Serial.println(event.gyro.y);
  delay(200);
}
