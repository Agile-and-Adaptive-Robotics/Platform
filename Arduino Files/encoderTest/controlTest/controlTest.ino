/* 
Test the control system of the balance platform with an encoder measuring the angle and a pot controlling the platform
Jake Chung
Dec-15-2019
*/

/*----------------------- Included Libraries  --------------------------------*/
#include <SPI.h>          //For communicating with DAC

//Dac Library information at http://arduino.alhin.de/index.php?n=8
#include <AH_MCP4921.h>   //For easy DAC functions

/*----------------------- Definitions  --------------------------------*/
AH_MCP4921 AnalogOutput(51, 52, 53);          //SPI communication is on Arduino MEGA Pins 51, 52, 53

/*------------------------Encoder setup------------------------------------*/
int counter = 180;
int aState;

//Pot setup
int InputPin = A0;

void setup() {
	//Serial.begin(9600);
	pinMode(InputPin, INPUT);
	PinMode(encA, INPUT);
	PinMode(encB, INPUT);
}

void loop() {
 	//read the encoder 
	aState = digitalRead(encA);
	//If the output of B pin is not the same as pin A, then the encoder rotates the the left
	if (digitalRead(encB) != aState) {
		counter = counter + 360/2048;
	} else {
		counter = counter - 360/2048;
	}
