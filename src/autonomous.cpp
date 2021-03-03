#include "custom/autonomous.h"

Robot Bongo;
void autonomous() {
  Vincent.reset();
  while (Vincent.is_calibrating()) {
    delay(5);
  }
  Bongo.Autonomous();
}
