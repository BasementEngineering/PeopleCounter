#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>

#include "Config.h"
#include "errorCodes.h";

#include "webUi.h"
#include "TofSensor.h"
#include "PeopleCounter.h"

const char* ssid = STASSID;
const char* password = STAPSK;

#define ENABLE_DEBUG

TofSensor myTofSensor;
PeopleCounter peopleCounter;

void blinkLed(int times, int interval = 500);

void setup() {  
  #ifdef ENABLE_DEBUG
  Serial.begin(115200);
  Serial.println("Setup starting");
  delay(5000);
  #endif
  pinMode(LED_BUILTIN,OUTPUT);

  #ifdef AP_MODE
  if(WiFi.softAP(ssid, password) ){           // Start the access point
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());         // Send the IP address of the ESP8266 to the computer
  }
  else{
    Serial.println("AP Failed");
  }
  #endif
  #ifndef AP_MODE
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  #endif

  Serial.println("Ready");
  
  myTofSensor.setup();
  peopleCounter.setSensor(&myTofSensor);
  setupWebUi(&peopleCounter);
}

unsigned long lastLedUpdate = 0;

void loop() {

  if( (millis() - lastLedUpdate) > 1000 ){
    digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
    lastLedUpdate = millis();
  }
  
  updateWebUi();
  yield();

  myTofSensor.update();
  peopleCounter.update();
}


void blinkLed(int times, int interval){
  for(int i = 0; i < times; i++){
    digitalWrite(LED_BUILTIN,LOW);
    delay(interval);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(interval);
  }
}
