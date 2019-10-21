/*This sketch tests what interrupt speed works with the DAC communication speed
 * 
 */

#include <SPI.h>          //For communicating with DAC

//Dac Library information at http://arduino.alhin.de/index.php?n=8
#include <AH_MCP4921.h>   //For easy DAC functions

AH_MCP4921 AnalogOutput(51, 52, 53);          //SPI communication is on Arduino MEGA Pins 51, 52, 53

int DACSignal = 0;

void setup() {
  InterruptSetup(); 

}

void loop() {
}


void InterruptSetup(){
  cli();//stop interrupts
  
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 1249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

ISR(TIMER1_COMPA_vect){
  DACSignal += 100;
  if(DACSignal >= 4095){
    DACSignal = 0;
  }
  AnalogOutput.setValue(DACSignal);
}
