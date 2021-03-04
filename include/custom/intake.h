#ifndef INTAKE
#define INTAKE
#include "math.h"
class intakeClass {
private:

  double intakespeed = 100;
  double deg = 0;
  bool isflush       = false;
  bool moving        = false;
  bool opposite      = false;
  bool keep = false;
  double pVal = .2;

public:

  Math myMath;
  //target middle
  double middle = 500;
  //lower end bound can go lower
  double small = 0;
  //higher end bound can go higher
  double large = 800;

  // stops intakes
  void stopBoth() {
    LArm.move_velocity(0);
    RArm.move_velocity(0);
  }

  void update() {
    if(moving){
      LArm.move_velocity(myMath.toRPM(isflush, intakespeed, LArm.get_gearing()));
      RArm.move_velocity(myMath.toRPM(!isflush, intakespeed, RArm.get_gearing()));
    } else if (keep){
      //LArm.move_velocity(myMath.toRPM(isflush, pVal * (deg - ), LArm.get_gearing()));
      RArm.move_velocity(myMath.toRPM((deg - rightArm.get_value()) < 0, fabs(pVal * (deg - rightArm.get_value())), RArm.get_gearing()));
    } else {
      stopBoth();
    }
  }
  void activate(bool setting, bool other = false) {
    moving = setting; opposite = other;
  }

  void keepAtPos(double degg){
    deg = degg;
  }

  void holdPos(bool keepp){
    keep = keepp;
  }

  // sets flush
  void open(bool setting) {
    isflush = setting;
  }
};
#endif // ifndef INTAKE
