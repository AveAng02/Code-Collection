#include <WiFi.h>
#include <PubSubClient.h>
#include <String>

// WiFi
const char *ssid = "AyanAcharyaWifi"; // Enter your Wi-Fi name
const char *password = "AyanWifi";  // Enter Wi-Fi password

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *topic = "esptopic/esp32";
const char *mqtt_username = "myesptest";
const char *mqtt_password = "myesptest";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    pinMode(22, OUTPUT);
    // Set software serial baud to 115200;
    Serial.begin(115200);
    // Connecting to a WiFi network
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the Wi-Fi network");
    //connecting to a mqtt broker
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback(callback);
    while (!client.connected()) {
        String client_id = "esp32-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Public EMQX MQTT broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.println(client.state());
            delay(2000);
        }
    }
    // Publish and subscribe
    client.publish(topic, "Hi, I'm ESP32 ^^");
    client.subscribe(topic);
}

void callback(char *topic, byte *payload, unsigned int length) {
    String cmd = "";
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
        cmd += (char) payload[i];
    }
    Serial.println();
    Serial.println("-----------------------");

    if(cmd == "ON" || cmd == "on")
    {
      digitalWrite(22, HIGH);
    }

    if(cmd == "OFF" || cmd == "off")
    {
      digitalWrite(22, LOW);
    }
}

void loop() {
    client.loop();
}
