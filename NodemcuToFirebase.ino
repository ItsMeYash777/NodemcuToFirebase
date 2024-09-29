// remember to install firebase lib by mobizt and esp8266
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h> 

// Wi-Fi credentials
#define WIFI_SSID "Your ssid"           
#define WIFI_PASSWORD "password"   

// Firebase setup
FirebaseData firebaseData;              
FirebaseAuth auth;                      
FirebaseConfig config;  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Connected to Wi-Fi!");
  config.host = "your host address"; // your real database url 
  config.signer.tokens.legacy_token = "your legacy token"; //Go to Project settings->Service Accounts->Data secrets
  Firebase.begin(&config, &auth);
  if (Firebase.ready()) {
    Serial.println("Firebase connected and ready!");
  } else {
    Serial.println("Failed to connect to Firebase");
  }
}

}

void loop() {
  // put your main code here, to run repeatedly:

}
