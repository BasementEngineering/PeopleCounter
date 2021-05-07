#include "Sensor.h"
#include <Arduino.h>

uint8_t zoneX = 15;
uint8_t zoneY = 8;

uint8_t opticalCenters[2] = {
  68,
  188
};

Sensor::Sensor():
myTofSensor()
{}

void Sensor::setup(){
      Wire.begin(4,5);//SDA,SCL
      delay(100);
      if(myTofSensor.begin() != 0){
        Serial.println("Sensor error");
      }
      
      myTofSensor.setDistanceModeLong();
      myTofSensor.setTimingBudgetInMs(20);
      
      startMeasurement();
  }

  void Sensor::startMeasurement(){
    myTofSensor.stopRanging();
    myTofSensor.clearInterrupt();
    myTofSensor.setROI(zoneX,zoneY,opticalCenters[currentZone]);
    myTofSensor.startRanging();
  }

  void Sensor::getResult(){
    int distance = myTofSensor.getDistance();
    if(currentZone == 0){
      //Serial.print("Zone1: ");Serial.println(distance);
      zone1 = personPresent(distance); 
    }
    else{
      //Serial.print("Zone2: ");Serial.println(distance);
      zone2 = personPresent(distance); 
    }
  }

  void Sensor::update(){
      if(myTofSensor.checkForDataReady()){
        getResult();
        if( (currentZone == 1) && !newDataAvailable){
          newDataAvailable = true;
        }
        
        currentZone = !currentZone;
        startMeasurement();     
      }
  }

  bool Sensor::dataAvailable(){
    if(newDataAvailable){
      newDataAvailable = false;
      return true;
    }
    return false;
  }

  bool Sensor::getZone1(){
    return zone1;
  }
  
  bool Sensor::getZone2(){
    return zone2;
  }


  bool Sensor::personPresent(int distance){
    //return ( (DOOR_THRESHOLD < distance) && (distance < PERSON_THRESHOLD) );
    return distance < PERSON_THRESHOLD ;
  }
