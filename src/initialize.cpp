#include "custom/autonomous.h"
bool PREAUTON;

void initialize() {
  //set Stopping for all motors
  FL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  FR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BL.set_brake_mode(E_MOTOR_BRAKE_COAST);
  BR.set_brake_mode(E_MOTOR_BRAKE_COAST);
  Flywheel.set_brake_mode(E_MOTOR_BRAKE_COAST);
  Lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  RArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

  delay(250);
  PREAUTON = Bongo.init();
}

void disabled() {}

void competition_initialize() {}
