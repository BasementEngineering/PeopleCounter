#ifndef PEOPLE_COUNTER_H
#define PEOPLE_COUNTER_H

#include "Sensor.h"

class PeopleCounter{
  public:
    PeopleCounter();
    void setSensor(Sensor* sensor);
    int update();
    int getCount();
    void reset();
    void setCount();
    void setLimit();

  private: 
    Sensor* mySensor =NULL;
    int count = 0;
    
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
