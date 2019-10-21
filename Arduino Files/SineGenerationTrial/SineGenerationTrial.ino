/*This sketch is meant to test generation of a sine wave through the DAC*/
/*----------------------- Included Libraries  --------------------------------*/
#include <SPI.h>          //For communicating with DAC

//Dac Library information at http://arduino.alhin.de/index.php?n=8
#include <AH_MCP4921.h>   //For easy DAC functions


/*----------------------- Definitions  --------------------------------*/
AH_MCP4921 AnalogOutput(51, 52, 53);          //SPI communication is on Arduino MEGA Pins 51, 52, 53

/*----------------------- Sine Wave Parameters ------------------------*/
float Period = 0.5;                    //Best starting at about 0.5 seconds
float PtPAmplitude = 4.0;  
float InterruptRate = 0.02;
int counter = 0;

void setup() {
  //Serial.begin(9600);
  InterruptSetup(); 
  
}

void loop() {
  int t = millis();
  //Serial.println(t);
  if(t > 10000){
    TIMSK1 = 0;
    AnalogOutput.setValue(4096/2);
    while(1){
      
    }
  }

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

ISR(TIMER1_COMPA_vect){
  float Output = PtPAmplitude/2*sin((counter*InterruptRate)*2*PI/Period);
  float DACOutput = Output/5.0*4096.0+4096.0/2.0;

  if(DACOutput > 4095.0){
    DACOutput = 4095.0;
  }
  else if(DACOutput < 0.0){
    DACOutput = 0.0;
  }
  //Serial.print("Counter:  "); Serial.print(counter); Serial.print("  "); Serial.print("Sine Value: "); Serial.print(Output); Serial.print("      DAC Value: "); Serial.println(DACOutput);

  counter += 1;
  if (counter*InterruptRate >= Period){
    counter = 0;
  }
  AnalogOutput.setValue((int) DACOutput);
}
