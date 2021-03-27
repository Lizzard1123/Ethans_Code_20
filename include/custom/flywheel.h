#ifndef FLYWHEEL
#define FLYWHEEL
#include "math.h"
class flywheelClass {
private:

  double flywheelspeed   = 40;
  bool flywheeltoggle    = false;
  bool currentOutputBall = false;

public:

  double speedLow    = 45;
  double speedMedium = 55;
  double speedHigh   = 100;
  Math myMath;

  // toggles flywheel
  void flywheeltoggleswitch() {
    flywheeltoggle = !flywheeltoggle;
  }

  void flywheelset(bool setting) {
    flywheeltoggle = setting;
  }

  // updates it
  void update() {
    if (flywheeltoggle) { // change flywheel % in double
      if (currentOutputBall) {
        printf("Back?");
        Flywheel.move_velocity(myMath.toRPM(true, flywheelspeed,
                                            Flywheel.get_gearing()));
      } else {
        Flywheel.move_velocity(myMath.toRPM(false, flywheelspeed,
                                            Flywheel.get_gearing()));
      }
    } else { // idle
      Flywheel.move_velocity(0);
    }
  }

  bool getSpeed() {
    return flywheelspeed;
  }

  bool getToggle() {
    return flywheeltoggle;
  }

  void outputBall(bool setting) {
    currentOutputBall = setting;
  }

  void setSpeed(double speed) {
    flywheelspeed = speed;
  }
};
#endif // ifndef FLYWHEEL
