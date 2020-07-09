//This program is to test a sine generation algorithm and to understand it
//Author: Jake Chung
//This program is developed based on Dr.Hunt algorithm

#define SAMP_SIZE 50 //define the sample size of the sine value array

//Define the variables
int Amp = 800; //amplitude of the sine wave
float VerShift = 2047; //vertical shift of the sine wave
int Freq = 1; //Frequency of the sine wave (not angular frequency)
int i = 0; //counter
int SetPoint[SAMP_SIZE]; //the sine value array

void setup() {
  Serial.begin(9600);
  analogWriteResolution(12);
  //predefine the sine value array
  for (i=1; i<SAMP_SIZE; ++i){
    SetPoint[i] = Amp*sin(Freq*6.2832/SAMP_SIZE*i)+VerShift;
  }
  SetPoint[0] = 2047; //define the first value of the sine wave
}

void loop() {
  if (i>=SAMP_SIZE){
    i = 0;
  }
  Serial.println(SetPoint[i]);
  analogWrite(DAC0, SetPoint[i]);
  ++i;
  delay(10);
}
