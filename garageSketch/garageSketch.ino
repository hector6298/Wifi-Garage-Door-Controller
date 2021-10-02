
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>x
s
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "IdBYH4PBwUx_knQus368Jl8gvmqh5Kty";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";
const int trigger = 4;
BlynkTimer timer; 

void reconnectBlynk() {
  if (!Blynk.connected()) {

    Serial.println("Lost connection");
    if(Blynk.connect()) {
      Serial.println("Reconnected");
    }
    else {
      Serial.println("Not reconnected");
    }
  }
}



BLYNK_WRITE(V1){
  digitalWrite(trigger,HIGH);
  delay(200);
  digitalWrite(trigger,LOW);
  Blynk.virtualWrite(V1,0);
}
void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  //digitalWrite(trigger, LOW);
  
  ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname("myesp8266");
  ArduinoOTA.setPassword("admin");
  
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }
    Serial.println("Start updating " + type);
  });
  
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  
  ArduinoOTA.begin();
  timer.setInterval(30*1000, reconnectBlynk); //run every 30s
}



void loop()
{
  ArduinoOTA.handle();
  Blynk.run();
}
