#include "peopleCounter.h"
#include "config.h"
#include "Arduino.h"
#include "errorCodes.h"

enum zoneNames{ZONE1 = 0, ZONE2 = 1};
enum events{NONE = 0,ENTERED = 1,LEFT = 2};
enum globalEvents{EnteredZ1 = 1, LeftZ1 = 2, EnteredZ2 = 3, LeftZ2 = 4};

PeopleCounter::PeopleCounter(){ 
}

void PeopleCounter::setSensor(Sensor* sensor){
  mySensor = sensor;
}
  
int PeopleCounter::update(){
  
  if(mySensor->dataAvailable()){
    int Z1,Z2,inside;
    
    Z1=mySensor->getZone1();
    Z2=mySensor->getZone2();
    inside = Z1 || Z2;

    if( !prevInside && inside ){
       int event = getGlobalEvent(Z1,Z2);
       if(event < 0){
        return event;
       }
      entry = event;
    }
    else if(prevInside && !inside){
      int event = getGlobalEvent(Z1,Z2);
       if(event < 0){
        return event;
       }
      exit = event;
      int result = evaluate(entry,exit);
      
      #ifdef MOUNTED_INSIDE
      result=-result;
      #endif
      
      count += result;
    }

    prevInside = inside;
    prevZ1 = Z1;
    prevZ2 = Z2;
    return RESULT_OK;
 }
}

int PeopleCounter::getCount(){
    return count;
  }

void PeopleCounter::setCount(int value){
  count = value;
}

int PeopleCounter::getLimit(){
  return limit;
}

void PeopleCounter::setLimit(int value){
  limit = value;
}

int PeopleCounter::getSingleZoneEvent(bool prevState,bool currentState){
  if(prevState == currentState){
    return NONE;
  }
  else if(!prevState && currentState){
    return ENTERED;
  }
  else if(prevState && !currentState){
    return LEFT;
  }
}

int PeopleCounter::getGlobalEvent(bool zone1, bool zone2){
  int Z1Event = getSingleZoneEvent(prevZ1,zone1);
  int Z2Event = getSingleZoneEvent(prevZ2,zone2);

  if(Z1Event && Z2Event){ //if two events happened simultaniously the person is too fast for the sensor (unable to tell direction)
    return PERSON_TOO_FAST;
  }

  if(Z1Event == ENTERED){
    #ifdef DEBUG_COUNTER
    Serial.println("Entered Zone 1");
    #endif
    return EnteredZ1;
  }
  else if(Z1Event == LEFT){
    #ifdef DEBUG_COUNTER
    Serial.println("Left Zone 1");
    #endif
    return LeftZ1;
  }

  if(Z2Event == ENTERED){
    #ifdef DEBUG_COUNTER
    Serial.println("Entered Zone 2");
    #endif
    return EnteredZ2;
  }
  else if(Z2Event == LEFT){
    #ifdef DEBUG_COUNTER
    Serial.println("Left Zone 2");
    #endif
    return LeftZ2;
  }
}

int PeopleCounter::evaluate(int entry, int exit){
  #ifdef DEBUG_COUNTER
  Serial.print("Evaluating: ");
  #endif
  
  if( ( entry == EnteredZ1 ) && ( exit == LeftZ2 ) ){
    #ifdef DEBUG_COUNTER
    Serial.println("+1");
    #endif
    return +1;
  }
  else if( ( entry == EnteredZ2 ) && ( exit == LeftZ1 ) ){
    #ifdef DEBUG_COUNTER
    Serial.println("-1");
    #endif
    return -1;
  }
  #ifdef DEBUG_COUNTER
  Serial.println("");
  #endif
  return 0;
}
