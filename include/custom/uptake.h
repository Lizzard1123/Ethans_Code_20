#ifndef UPTAKE
#define UPTAKE
#include "math.h"
class uptakeClass {
private:

  int liftspeed = 50;
  bool toggled  = false;
  bool isflush  = false;
  bool output   = false;

public:

  Math myMath;
  void stopBoth() {
    Lift.move_velocity(0);
  }

  void update() {
    if (output) {
      stopBoth();
    } else if (toggled && !isflush) {
      Lift.move_velocity(myMath.toRPM(true, liftspeed, Lift.get_gearing()));
    } else if (isflush) {
      Lift.move_velocity(myMath.toRPM(false, liftspeed, Lift.get_gearing()));
    } else {
      stopBoth();
    }
  }

  void setToggle(bool setting) {
    toggled = setting;
  }

  void outputBall(bool setting) {
    output = setting;
  }

  void toggle() {
    toggled = !toggled;
  }

  bool getToggle() {
    return toggled;
  }

  // sets flush
  void setSpeed(double setting) {
    liftspeed = setting;
  }

  void flush(bool setting) {
    isflush = setting;
  }
};
#endif // ifndef UPTAKE
