/*This code is set up to attempt to write an array to the SD card*/
#include <SD.h>
float Period = 1.0;
float freq = 0.2;
int arraySize = Period/freq;
float myArray[5];

void setup() {
  Serial.begin(9600);
  



}

void loop() {
  
  for(int i = 0; i <= arraySize; i++){
    myArray[i] = i*20;
  }
  
  for(int i = 0; i <= arraySize; i++){
    Serial.println(myArray[i]);
  }
  
}
