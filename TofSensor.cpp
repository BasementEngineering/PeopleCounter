#include "TofSensor.h"
#include <Arduino.h>
#include <Wire.h>
#include "TofSensorConfig.h"

uint8_t opticalCenters[2] = {
  68,
  188
};

TofSensor::TofSensor():
Sensor(),myTofSensor()
{}

void TofSensor::setup(){
      Wire.begin(4,5);//SDA,SCL //WEMOS Labels: D2,D1
      delay(100);
      if(myTofSensor.begin() != 0){
        Serial.println("Sensor error");
      }
      
      myTofSensor.setDistanceModeLong();
      myTofSensor.setTimingBudgetInMs(20);
      
      startMeasurement();
  }

void TofSensor::update(){
      if(myTofSensor.checkForDataReady()){
        getResult();
        if( (currentZone == 1) && !newDataAvailable){
          newDataAvailable = true;
        }
        
        currentZone = !currentZone;
        startMeasurement();     
      }
}

  void TofSensor::startMeasurement(){
    myTofSensor.stopRanging();
    myTofSensor.clearInterrupt();
    myTofSensor.setROI(zoneX,zoneY,opticalCenters[currentZone]);
    myTofSensor.startRanging();
  }

  void TofSensor::getResult(){
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



  bool TofSensor::personPresent(int distance){
    //return ( (DOOR_THRESHOLD < distance) && (distance < PERSON_THRESHOLD) );
    return distance < PERSON_THRESHOLD ;
  }
