int PotPin = A1;
int PotValue;

void setup() {
  pinMode(PotPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  PotValue = analogRead(PotPin);
  Serial.println(PotValue);
  delay(100);

}
