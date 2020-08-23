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
#define FreqSamplingSize 10

/*----------------------- Sine Wave Parameters ------------------------*/
float PtPAmplitude = 2;  
float InterruptRate = 0.02;
volatile int counter = 0;
int i = 0; //counter for for loop
volatile int j = 0; //counter for the Frequency Array to loop through all frequencies
volatile unsigned long timeCounter = 0; //this is a time counter to count to 10 seconds to get to a new frequency

//Set up data collection
float FreqArr[FreqSamplingSize];
float lowThres = 0.2;
float highThres = 1.35;
volatile unsigned long t = 0; //variable to store the millis value

/*----------------------- Control Parameters ------------------------*/
float DACoffset = 4096.0/2.0;
float Kp = 1;
int pos = 0; //initialize the variable for encoder read

//Encoder set up
Encoder myEnc(encA, encB);

void setup() {
  Serial.begin(115200);
  //Set up the Frequency Array that contains the frequency the interrupt will output
  for (i=0; i < FreqSamplingSize; i++) {
    FreqArr[i] = lowThres +(highThres-lowThres)*i/FreqSamplingSize;
  }
  InterruptSetup();
  delay(500); //delay for everything to catch up
  while (!Serial) {
    ; // wait for serial port to connect
  }
}

void loop() {
  t = millis()/10000;
  //count the number of milisecond ellapses since the program runs. Because of the type, it will always round up. 
  //If want a different counting period, change the 10000 number
  if(j > FreqSamplingSize){
    TIMSK1 = 0; //turn off the interrupt
    AnalogOutput.setValue(4096/2);
    while(1){
      //does nothing
    }
  }
}

void InterruptSetup(){
  cli();//stop interrupts
  
  //set timer0 interrupt at 50 Hz (20ms)
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

//This function handle the printing to serial
void writeData2Serial(int encoderVal, float DACVal ){
  Serial.print(encoderVal);
  Serial.print(" ");
  Serial.println(DACVal);
}

ISR(TIMER1_COMPA_vect){
  float Period = 1/FreqArr[j];
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
  pos = myEnc.read(); //for some reason, you need this line, otherwise the interrupt would break
  float encAngle = 360.0/8192.0 * pos; //convert to degrees 2048 pulses per revolution
  float encBit = 4096.0/10.0*encAngle; //convert read angle degree to binary of DACoutput to compute error correctly
  float error = (DACOutput - 2048.0) - encBit; //Compute error. This error is in binary (DACOutput - 2048) is to shfit the sine wave to 0
  float DACsignal = Kp*error + DACoffset;//Need DACoffset because the signal goes from 0 to 4096

  if(DACsignal > 4095.0){
    DACsignal = 4095.0;
  }
  else if(DACsignal < 0.0){
    DACsignal = 0.0;
  }
  AnalogOutput.setValue((int) DACsignal);
  //Serial.println(DACsignal); //uncomment when the code need to be debugged
  if (t > timeCounter){
    j++; //increment j to the next index when the time is greater than the counter. Effectively toggle after 10 seconds.
    timeCounter = t;
    writeData2Serial((float) -99,(int) -99); //printing a -1 in the data to know where the switch to the next frequency
  } else {
    writeData2Serial(pos, (float) DACOutput);
  }
  //Serial.println(pos);
  //Serial.print(" Enc Vol: ");
  //Serial.print(encVol);
  //Serial.print(" DACerror: ");
  //Serial.print(error);
  //Serial.print(" DAC Signal: ");
  //Serial.println(DACsignal);
}
