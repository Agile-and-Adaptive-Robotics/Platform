//Author: Jake Chung
//Quick program to test the speed of the loop on the Arduino Due
int counter = 0; //variable to count the number of loops within 20ms
int i = 0; //for loop counter
int t = 0; //for mullis

//Try to stress out the loop by adding some pseudo calculations
float Amplitude = 2;  
float freq = 0.5;
//float out;

void setup() {
  Serial.begin(9600);
}
void loop() {
  t = millis();
  if (t > 2000){
    if (t < 2020){
      counter += 1;
      float out = Amplitude*sin((counter*0.02)*2*PI*freq);
    } else {
      Serial.println(counter);
      Serial.println(t);
      //Serial.println(out);
      while(1){
        //does nothing
      }
    }
  }
}
