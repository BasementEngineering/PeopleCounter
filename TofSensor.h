#ifndef TOF_SENSOR_H
#define TOF_SENSOR_H

#include "Sensor.h"
#include <SparkFun_VL53L1X.h>

class TofSensor : public Sensor{

public:
  TofSensor();
  void setup() override;
  void update() override;

private:
  SFEVL53L1X myTofSensor;
  int currentZone = 0;

  void startMeasurement();
  void getResult();
  bool personPresent(int distance);
};

#endif
