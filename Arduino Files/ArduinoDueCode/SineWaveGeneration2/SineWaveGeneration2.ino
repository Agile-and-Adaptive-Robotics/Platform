//Author: Jake Chung
//July 24, 2020
//This program generate a sinusoidal pattern and send it to the DAC of the Due
int counter = 0;//counter for keeping track of the counter period
int counterPeriod = 50; //20ms sampling rate of the sine wave
int i = 0; //general counter for loop
unsigned long t = 0; //variable for the millis function

//Set up the sinusoidal parameters
float Amplitude = 0.5; //unitless sine wave, scale depending on the output voltage.
float freq = 2; //frequency in Hz
float scaler = 2048; //scaler to the DAC binary output

void setup() {
  Serial.begin(115200);
  analogWriteResolution(12);
}

void loop() {
  t = millis()/counterPeriod; 
  if (t > counter){
    counter = t; //basic algorithm to increment the counter
    float out = scaler*Amplitude*sin((counter*counterPeriod*0.001)*2*PI*freq)+2048;
    analogWrite(DAC0, (int) out);
    //Serial.println(out);
  }


}
