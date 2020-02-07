/* 
Test the control system of the balance platform with an encoder measuring the angle and a pot controlling the platform
Jake Chung
Dec-15-2019
*/

/*----------------------- Included Libraries  --------------------------------*/
#include <SPI.h>          //For communicating with DAC
#include <Encoder.h>	 

//Dac Library information at http://arduino.alhin.de/index.php?n=8
#include <AH_MCP4921.h>   //For easy DAC functions

//Encoder pins
#define encA 2
#define encB 3

/*----------------------- Definitions  --------------------------------*/
AH_MCP4921 AnalogOutput(51, 52, 53);          //SPI communication is on Arduino MEGA Pins 51, 52, 53

//Pot set up
int InputPin = A1;

//Encoder set up
Encoder myEnc(encA, encB);

//Controller set up
float KP = 1.0;
float DACoffset = 4096.0/2.0;

void setup() {
	Serial.begin(112500);
	pinMode(InputPin, INPUT);
}

void loop() {
 	//read the encoder 
	float pos = myEnc.read();
	float encAngle = 10.0/226.0*pos;
	
	float posValue = analogRead(InputPin);
	float posAngle = 10.0/256.0*posValue - 20.0;
	
	float error = encAngle - posAngle; 
	float DACerror = error*4096.0/20.0;
	float DACsignal = KP*DACerror + DACoffset;
	
    if(DACsignal > 4095.0){
      DACsignal = 4095.0;
    }
    else if(DACsignal < 0.0){
      DACsignal = 0.0;
    }
    AnalogOutput.setValue((int) DACsignal);
}
