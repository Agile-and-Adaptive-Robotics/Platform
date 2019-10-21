#include <SPI.h>
#include <AH_MCP4921.h>

AH_MCP4921 AnalogOutput(51, 52, 53);

int OutputSignal = 0;
  float offset = 2.5;
  float amp = 1.0;
  //float freq = 1.0*PI/180.0;
  float freq = 1.0*2.0*PI;
  int startTime = millis();
  int Period = 1000;

int InputSignalPin = A0;
int InputValue;



void setup() {
  pinMode(InputSignalPin, INPUT);

}

void loop() {
  InputValue = analogRead(InputSignalPin);
  OutputSignal = InputValue*(4095/1023);
  AnalogOutput.setValue(OutputSignal);
  delay(1);

  
  /*
  for(int i = 1000; i <= 3095; i=i+10){
    AnalogOutput.setValue(i);
    delay(1);
  }
  */
  /*
  while(1){
    int currentTime = millis();
    int pos = currentTime%Period;
    float BalanceSignal = amp*sin(freq*pos)+offset;
    //int OutputSignal = map(BalanceSignal, 0, 5, 0, 4095);
    int OutputSignal = BalanceSignal*(4095/5);
    //Serial.print(BalanceSignal); Serial.print("       "); Serial.println(OutputSignal);
    AnalogOutput.setValue(OutputSignal);
    delay(10);
  }
  */
  
  
}
