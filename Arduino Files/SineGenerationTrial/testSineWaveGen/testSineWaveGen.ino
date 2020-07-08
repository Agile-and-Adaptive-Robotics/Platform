//This program is to test a sine generation algorithm and to understand it
//Author: Jake Chung
//This program is developed based on Dr.Hunt algorithm

#define SAMP_SIZE 100 //define the sample size of the sine value array

//Define the variables
int Amp = 1; //amplitude of the sine wave
byte VerShift = 128; //vertical shift of the sine wave
int pin = 3;
int Freq = 1; //Frequency of the sine wave (not angular frequency)
int i = 0; //counter
byte SetPoint[SAMP_SIZE]; //the sine value array

void setup() {
  Serial.begin(9600);
  //predefine the sine value array
  for (i=1; i<SAMP_SIZE; ++i){
    SetPoint[i] = Amp*sin(Freq*6.2832/SAMP_SIZE*i)+VerShift;
  }
  SetPoint[0] = 128; //define the first value of the sine wave
  pinMode(pin, OUTPUT);
}

void loop() {
  if (i>=SAMP_SIZE){
    i = 0;
  }
  Serial.println(SetPoint[i]);
  analogWrite(pin, SetPoint[i]);
  ++i;
}
