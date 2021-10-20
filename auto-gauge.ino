//----------------------------------------------------------------------
// .... try make it all work....
//----------------------------------------------------------------------
#include "gauge.h"

// For motors connected to digital pins 4,5,6,7
Gauge main_gauge(0,1,2,3);

void setup(void)
{
  // run the motor against the stops
  Serial.begin(9600);
  main_gauge.zero();
  Serial.println("zero...");
}

void loop(void){
  for(int i = 0; i < 140; i++) {
    //show off some wiggle....
    main_gauge.setPosition(i);
  }
  main_gauge.demo();
}
