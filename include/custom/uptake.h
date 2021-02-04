#ifndef UPTAKE
#define UPTAKE
#include "math.h"
class uptakeClass {
private:

  int liftspeed = 50;
  bool toggled  = false;
  bool isflush  = false;

public:

  Math myMath;
  void stopBoth() {
    Lift.move_velocity(0);
  }

  void update() {
    if (toggled && !isflush) {
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

  void toggle() {
    toggled = !toggled;
  }

  bool getToggle() {
    return toggled;
  }

  int getSpeed(){
    return liftspeed;
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
