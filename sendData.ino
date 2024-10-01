#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "ssid";
const char* password = "password";
const char* server = "api.thingspeak.com";
const char* apiKey = "Thing speak api key";

#define MQ4_SENSOR A0       
#define GAS_THRESHOLD 315   
#define buzzerPin D1        
#define ledPin D2           

void setup() {
  pinMode(MQ4_SENSOR, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600); 
  connectToWiFi();
}

void loop() {
  int sensorValue = analogRead(MQ4_SENSOR);
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);
  
  sendToThingSpeak(sensorValue);
  
  if (sensorValue < GAS_THRESHOLD) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(500); 
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
    delay(500); 
  }
  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
}

void connectToWiFi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
}

void sendToThingSpeak(int value) {
  WiFiClient client;
  String url = "/update?api_key=";
  url += apiKey;
  url += "&field1=";
  url += String(value);
  if (client.connect(server, 80)) {
    Serial.println("Sending data to ThingSpeak...");
    client.print("GET " + url + " HTTP/1.1\r\n");
    client.print("Host: " + String(server) + "\r\n");
    client.print("Connection: close\r\n\r\n");
    delay(500);
    client.stop();
    Serial.println("Data sent to ThingSpeak");
  }
}
