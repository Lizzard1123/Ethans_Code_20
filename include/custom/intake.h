#ifndef INTAKE
#define INTAKE
#include "math.h"
class intakeClass {
private:

  double intakespeed = 100;
  bool isflush       = false;
  bool moving        = false;
  bool opposite      = false;

public:

  Math myMath;

  // stops intakes
  void stopBoth() {
    LArm.move_velocity(0);
    RArm.move_velocity(0);
  }

  void update() {
    // if moving and not flushing
    // spin intakes inward
    if (moving && !isflush) {
      // spins left opposite
      if (opposite) {
        LArm.move_velocity(myMath.toRPM(true, intakespeed, LArm.get_gearing()));
      } else {
        LArm.move_velocity(myMath.toRPM(false, intakespeed, LArm.get_gearing()));
      }
      RArm.move_velocity(myMath.toRPM(true, intakespeed, RArm.get_gearing()));

      // if the intakes are flusing  reverse intakes
    } else if (isflush) {
      if (opposite) {
        LArm.move_velocity(myMath.toRPM(false, intakespeed, LArm.get_gearing()));
      } else {
        LArm.move_velocity(myMath.toRPM(true, intakespeed, LArm.get_gearing()));
      }
      RArm.move_velocity(myMath.toRPM(false, intakespeed, RArm.get_gearing()));
    } else {
      stopBoth();
    }
  }

  void activate(bool setting, bool other = false) {
    moving = setting; opposite = other;
  }

  // sets flush
  void open(bool setting) {
    isflush = setting;
  }
};
#endif // ifndef INTAKE
