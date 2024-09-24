void setup() {
   pinMode(22, OUTPUT);
   Serial.begin(115200);
}
  
void loop() {
   digitalWrite(22, HIGH);
   delay(500);
   digitalWrite(22, LOW);
   delay(500);
   Serial.println("hello World");
   delay(500);
}
