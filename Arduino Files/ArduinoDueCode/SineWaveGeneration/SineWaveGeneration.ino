//Author: Jake Chung
//07-23-2020
//This code generate a sinusoidal pattern at specified frequencies for system identification
//This code should be run on a Due at logic level 3.3V
//This coed is built off of the SineGenerationTrial program

#define FreqSamplingSize 10

//Set up the sine wave properties
float Amplitude = 1;
float InterruptRate = 0.02;
int counter = 0; //counter for sine wave
int i = 0; //counter for for loop
int j = 0; //counter for Frequency Array to loop through the different frequencies
unsigned long timeCounter = 0; //this is a time counter to count to 10 seconds to get to a new frequency

//Set up for frequency array
float FreqArr[FreqSamplingSize];
float lowThres = 0.2;
float highThres = 1.35;
unsigned long t = 0; //store the millis() function 

void setup() {
  Serial.begin(115200);
  //analogWriteResolution(12); //set up DAC resolution
  //Set up for frequency Array
  for (i=0; i < FreqSamplingSize; i++) {
    FreqArr[i] = lowThres +(highThres-lowThres)*i/FreqSamplingSize;
  }
  InterruptSetup();
  delay(500); //this delay seems to work so the interrupt routine has time to execute
  /*
  while (!Serial) {
    ; // wait for serial port to connect
  }
  */

}

void loop() {
  t = millis()/10000;
  //count the number of milisecond ellapses since the program runs. Because of the type, it will always round up. 
  //If want a different counting period, change the 10000 number
  if(j > FreqSamplingSize){
    TIMSK1 = 0; //turn off the interrupt
    analogWrite(DAC0, (float) 1.65);
    Serial.println("Program is done.");
    while(1){
      //does nothing
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

ISR(TIMER1_COMPA_vect){ //interrupt service routine to run execute periodically to generate the sine wave
  float SineOut = Amplitude*sin((counter*InterruptRate)*2*PI*FreqArr[j]); //sine wave
  float DACOutput = SineOut*1.1 + 1.65; //convert sine wave to DAC output on the Due

  if(DACOutput > 2.75){
    DACOutput = 2.75;
  }
  else if(DACOutput < 0.55){
    DACOutput = 0.55;
  }

  counter += 1;
  if (counter*InterruptRate >= 1/FreqArr[j]){
    counter = 0;
  }
  
  analogWrite(DAC0, DACOutput);
  if (t>timeCounter){
    j++; //increment j to the next index when the time is greater than the counter. Effectively toggle after 10 seconds.
    timeCounter = t;
  } 
}
