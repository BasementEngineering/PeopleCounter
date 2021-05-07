#ifndef SENSOR_H
#define SENSOR_H

#include <Wire.h>
#include <SparkFun_VL53L1X.h>
#include "SensorConfig.h"

class Sensor{

public:
  Sensor();
  void setup();
  void update();
  bool dataAvailable();
  bool getZone1();
  bool getZone2();

private:
  SFEVL53L1X myTofSensor;
  
  bool zone1 = false;
  bool zone2 = false;
  int currentZone = 0;
  bool newDataAvailable = false;

  void startMeasurement();
  void getResult();
  bool personPresent(int distance);

};

#endif
