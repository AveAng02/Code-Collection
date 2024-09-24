#include <SoftwareSerial.h>

SoftwareSerial ESP8266(2, 3); // RX, TX
String str;

String setCommand(String str);

void setup() {
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  Serial.begin(115200);
  ESP8266.begin(115200);
}


void loop() 
{
  ESP8266.println("AT+CIFSR");
  
  while(ESP8266.available()){
    str += String(char(ESP8266.read()));

    if(ESP8266.overflow()){
      Serial.println("We have a overflow");
      break;
    }
  }

  Serial.println(str);
  delay(1000);
  ESP8266.write(" ");            
}


String setCommand(String str){
  int c = 0;
  while(ESP8266.available() && c < 200){
    str += String(char(ESP8266.read()));
    c++;

    if(ESP8266.overflow()){
      Serial.println("We have a overflow");
      break;
    }
  }
}
