#include "WiFi.h"

const char* ssid = "AyanAcharyaWifi";
const char* password =  "AyanWifi";

void blinkConnect();

void setup() {
  pinMode(32, OUTPUT);
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Wifi status ");
    Serial.println(WiFi.status());
    digitalWrite(32, HIGH);
    delay(1000);
    digitalWrite(32, LOW);
    delay(1000);
  }
 
  Serial.println("Connected to the WiFi network");
}
 
void loop() {}
