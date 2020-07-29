unsigned long counter = 0;
int j = 0; //counter for the Frequency Array to loop through all frequencies
unsigned long timeCounter = 0; //this is a time counter to count to 10 seconds to get to a new frequency


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  

}

void loop() {
  //count the number of milisecond ellapses since the program runs. Because of the type, it will always round up. 
  //If want a different counting period, change the 10000 number
  unsigned long t = millis()/5000; 
  if(t>timeCounter){
    j++; //increment j to the next index when the time is greater than the counter. Effectively toggle after 10 seconds.
    timeCounter = t; 
    //writeData2Serial(-1, -1); //printing a -1 in the data to know where the switch to the next frequency
    Serial.println(t); //for debugging
    Serial.println(millis());
  }
}
