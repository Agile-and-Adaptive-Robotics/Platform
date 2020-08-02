#include <SPI.h>
#include <AH_MCP4921.h>
#include <Encoder.h>      //For encoder 

//define the encoder pins
#define encA 19
#define encB 20

//Encoder set up
Encoder myEnc(encA, encB);

//DAC set up
AH_MCP4921 AnalogOutput(51, 52, 53);

//declare variables
float desirePos = 2048; //position set by the serial port
int pos = 0; //position read by the encoder
String readStr;
float readVoltage;
float err;
float DACinput;


void setup() {
  Serial.begin(115200);
  delay(200); //need this delay to set the value of the DAC
  AnalogOutput.setValue(pos); //initiate at the 0 position.
}

void loop() {
  if(Serial.available()){ //wait for serial to read
    readStr = Serial.readString(); //use readString to read the entire number
    desirePos = readStr.toInt(); //convert string to integer
    desirePos = 2.5/2048*desirePos;
  }
  //apply negative feedback 
  pos = myEnc.read();
  readVoltage = 0.25*(pos*0.17578)+2.5; //convert encoder pulses to voltage
  err = desirePos - readVoltage; //calculate error
  float DACVoltage = err + 2.5; //offset the error
  DACinput = 2048/2.5*DACVoltage; 
  AnalogOutput.setValue((int) DACinput);
  
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
