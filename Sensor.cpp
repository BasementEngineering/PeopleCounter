#include "Sensor.h"

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
