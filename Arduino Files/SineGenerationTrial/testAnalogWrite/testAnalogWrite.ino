/*Test analogWrite function on the Due
 * Jake Chung
*/

int pin = 3;

void setup() {
  Serial.begin(9600);
  pinMode(pin, OUTPUT);
}

void loop() {
  analogWrite(pin, 20);
}
