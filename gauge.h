
#ifndef GAUGE
#define GAUGE

#include "SwitecX25.h"

//#define STEPS (315*3) //gauge always has that many...
#define STEPS (600)

class Gauge {

  public:
    Gauge(unsigned char p1, unsigned char p2, unsigned p3, unsigned p4)
        : motor(STEPS, p1, p2, p3, p4), state(0), pos(0) {}
    ~Gauge() {}

    void setPosition(unsigned newPos) {
        if (newPos > 80) {
            Serial.print(newPos);
            Serial.println("wiggle...");
            wiggle();
        } else {
            pos = map(newPos, 0, 100, 0, STEPS);
        }
        move();
    }

    void zero(void) { motor.zero(); }

    // Demo function to go back and forward full range
    void demo(void) {
        int newPos = 0;
        int newDir = 1;
        while (1) {
            setPosition(newPos);
            newPos += newDir;
            if (newPos >= 100 || newPos <= 0)
                newDir *= -1; // turn around
        }
    }

  private:
    unsigned state;
    unsigned pos;
    int dir = 1;
    void wiggle(void) {
        /*do nothing*/
        pos += dir;
        if (pos >= 100 || pos <= 80)
            dir *= -1;
    }

    void move(void) {
        motor.setPosition(pos);

        motor.updateBlocking();
    }
    SwitecX25 motor;
};

#endif // GAUGE
