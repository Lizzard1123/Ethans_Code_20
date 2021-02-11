#include "custom/autonomous.h"

Robot Bongo;
void autonomous() {
  while (Vincent.is_calibrating()) {
    delay(5);
  }
  Bongo.Autonomous();
}
