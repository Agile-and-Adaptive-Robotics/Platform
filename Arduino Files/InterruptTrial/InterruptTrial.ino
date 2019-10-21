/* This code is meant to test an interrupt on a button. The purpose is to have a button switch the balance platform 
 *  voltage from 2.5 V (no motor movement) to a variable voltage (controlled by potentiometer or function generator)
 *  
 */

/*----------------------- Included Libraries  --------------------------------*/
#include <SPI.h>          //For communicating with DAC

//Dac Library information at http://arduino.alhin.de/index.php?n=8
#include <AH_MCP4921.h>   //For easy DAC functions


/*----------------------- Definitions  --------------------------------*/
AH_MCP4921 AnalogOutput(51, 52, 53);          //SPI communication is on Arduino MEGA Pins 51, 52, 53

const byte interruptPin = 2;            //attached to a button. Other end of button is attached to ground
boolean toggle = 0;

void setup() {
  pinMode(interruptPin, INPUT_PULLUP);        //Sets pin to be high when button is open, and low when button is pushed
  attachInterrupt(digitalPinToInterrupt(interruptPin), switchVoltage, FALLING);
  //Serial.begin(9600);
  
  InterruptSetup();

}

void loop() {
  
}

void InterruptSetup(){
  cli();//stop interrupts
  
  //set timer0 interrupt at 50 Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 1249;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10, CS11, and CS12 bits for 256 prescaler
  TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();//allow interrupts
}

void switchVoltage(){
  toggle = !toggle;
}

ISR(TIMER1_COMPA_vect){
  if(toggle == LOW){
    AnalogOutput.setValue(3000);
  }
  else if (toggle == HIGH){
    AnalogOutput.setValue(1000);
  }
}
