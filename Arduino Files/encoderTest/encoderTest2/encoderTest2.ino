/* Test the encoder using the encoder library */
#include <Encoder.h>
#define encA 2
#define encB 3

long pos = 0;
long newPos = 0;

//initiate the encoder lib
Encoder myEnc(encB, encA);

void setup() {
	Serial.begin(115200);
}

void loop() {
	pos = myEnc.read();
  if (pos != newPos) {
	  Serial.print("Position: ");
	  Serial.println(pos);
    newPos = pos;
  } 
}
	
