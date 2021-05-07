#ifndef SENSOR_H
#define SENSOR_H

class Sensor{

public:
  virtual void setup();
  virtual void update();
  bool dataAvailable();
  bool getZone1();
  bool getZone2();

protected:
  bool zone1 = false;
  bool zone2 = false;
  bool newDataAvailable = false;

};

#endif
