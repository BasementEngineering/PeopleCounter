#include "webUi.h"
#include "website.h"
#include "config.h"
#include "errorCodes.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WebSocketsServer.h>

ESP8266WebServer server(80);
WebSocketsServer socketServer = WebSocketsServer(81);

PeopleCounter* myPeopleCounter;

void handleRoot() {
    server.send(200, "text/html", homepage);
}

void handleCorrection(){
  server.send(200, "text/html", correctionForm);
}

void handleSetParameters(){
  int newCount = String(server.arg("count")).toInt();
  int newLimit = String(server.arg("limit")).toInt();

  if(newCount > -1){
    myPeopleCounter->setCount(newCount);
  }
  if( newLimit > -1){
    myPeopleCounter->setLimit(newLimit);
  }
  
  handleCorrection();
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void handleLimit(){
  server.send(200, "text/plain", String( myPeopleCounter->getLimit() ));
}

void updateCounter(){
  String count;
  int value = myPeopleCounter->getCount();
  count = String( value );
  server.send(200, "text/plain", count );
}

void setupWebUi(PeopleCounter* peopleCounter) {
  myPeopleCounter = peopleCounter;
  server.on("/", handleRoot);
  server.on("/count", updateCounter );
  server.on("/correction",handleCorrection);
  server.on("/setParameters",handleSetParameters);
  server.on("/limit", handleLimit);

  server.onNotFound(handleNotFound);

  server.begin();
  startWebsocket();
}

void updateWebUi(){
  server.handleClient();
  updateWebsocket();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) {
    case WStype_DISCONNECTED:       
      break;
    case WStype_CONNECTED: 
      break;
    case WStype_TEXT:        
      break;
  }
}

void startWebsocket() { // Start a WebSocket server
  socketServer.begin();                          // start the websocket server
  socketServer.onEvent(webSocketEvent);          // if there's an incomming websocket message, go to function 'webSocketEvent'
}

int lastCount = 0;
void updateWebsocket(){
    socketServer.loop();
    int count = myPeopleCounter->getCount();
    if(count != lastCount){
      String countMsg = String(count);
      socketServer.broadcastTXT(countMsg);
    }
    lastCount = count;
}

void sendErrorMessage(int error){
  if(error == SENSOR_TIMEOUT_ERROR){
    socketServer.broadcastTXT("Error: TofSensor timed out");
  }
  else if(error == PERSON_TOO_FAST){
    socketServer.broadcastTXT("Error: Person too fast");
  } 
}
