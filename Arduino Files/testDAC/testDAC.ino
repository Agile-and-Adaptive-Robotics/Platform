//quick program to test the DAC MCP4921
#include <SPI.h>
#include <AH_MCP4921.h>

AH_MCP4921 AnalogOutput(51, 52, 53); //define the DAC pins

int V = 2.5;

void setup() {
  AnalogOutput.setValue(V); //set voltage of the DAC

}

void loop() {
 
}
