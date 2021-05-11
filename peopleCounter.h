#ifndef PEOPLE_COUNTER_H
#define PEOPLE_COUNTER_H

#include "Sensor.h"
#include "config.h"

class PeopleCounter{
  public:
    PeopleCounter();
    void setSensor(Sensor* sensor);
    int update();
    int getCount();
    int getLimit();
    void setCount(int value);
    void setLimit(int value);

  private: 
    Sensor* mySensor;
    int count = 0;
    int limit = DEFAULT_PEOPLE_LIMIT;
    
    bool prevZ1 = false;
    bool prevZ2 = false;
    bool prevInside = false;
    int  entry = 0;
    int  exit = 0;

    void logEvent(bool zone1, bool zone2);

    int getState(int& Z1,int& Z2, int& inside);
    int getSingleZoneEvent(bool prevState,bool currentState);
    int getGlobalEvent(bool zone1, bool zone2);
    int evaluate(int entry, int exit);
};

#endif
