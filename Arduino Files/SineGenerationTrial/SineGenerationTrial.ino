/*This sketch is meant to test generation of a sine wave through the DAC*/
/*
 * Jake Chung: Build off of Connor's code to generate a sine wave pattern
 */
/*----------------------- Included Libraries  --------------------------------*/
#include <SPI.h>          //For communicating with DAC
#include <Encoder.h>      //For encoder 

//Dac Library information at http://arduino.alhin.de/index.php?n=8
#include <AH_MCP4921.h>   //For easy DAC functions]

/*----------------------- Definitions  --------------------------------*/
AH_MCP4921 AnalogOutput(51, 52, 53);          //SPI communication is on Arduino MEGA Pins 51, 52, 53

//define the encoder pins
#define encA 19
#define encB 20

/*----------------------- Sine Wave Parameters ------------------------*/
float Period = 0.5;                    //Best starting at about 0.5 seconds
float PtPAmplitude = 2;  
float InterruptRate = 0.02;
int counter = 0;
float DACoffset = 4096.0/2.0;
float Kp = 1;

//Encoder set up
Encoder myEnc(encA, encB);

void setup() {
  Serial.begin(115200);
  InterruptSetup(); 
}

void loop() {
  int t = millis();
  //Serial.println(t);
  if(t > 10000){
  //if(0){ //uncomment this for the interupt to run continuously
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
  
  //set up the negative feedback loop
  float pos = myEnc.read();
  float encAngle = 10.0/226.0*pos; //convert to degrees
  float encVol = 2.5/10.0*encAngle; //convert read angle to voltage

  float error = -Output + encVol;
  float DACerror = error*4096.0/5;
  float DACsignal = Kp*DACerror + DACoffset;

  if(DACsignal > 4095.0){
    DACsignal = 4095.0;
  }
  else if(DACsignal < 0.0){
    DACsignal = 0.0;
  }
  AnalogOutput.setValue((int) DACsignal);
  //Serial.print("Counter: "); 
  //Serial.print(counter);
  //Serial.print(" Sine Value: ");
  //Serial.print(Output);
  Serial.print(" Enc Vol: ");
  Serial.print(encVol);
  Serial.print(" DACerror: ");
  Serial.print(error);
  Serial.print(" DAC Signal: ");
  Serial.println(DACsignal);
}
