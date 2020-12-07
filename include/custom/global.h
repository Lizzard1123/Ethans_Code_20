#include "main.h"
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// FL                   motor         6
// FR                   motor         4
// BL                   motor         1
// BR                   motor         10
// LArm                 motor         11
// RArm                 motor         20
// Flywheel             motor         7
// Lift                 motor         8
// Vincent              inertial      5
// Vision               vision        21
// Controller1          controller
// leftOdom             encoder       A, B
// rightOdom            encoder       C, D
// IntakeSense          line          E
// outtakeSense         line          F
// TeamColor            pot           G
// AutonNumber          pot           H
// ---- END VEXCODE CONFIGURED DEVICES ----

//motors
extern Motor FL;
extern Motor FR;
extern Motor BL;
extern Motor BR;
extern Motor LArm;
extern Motor RArm;
extern Motor Flywheel;
extern Motor Lift;

//controllers
extern Controller Controller;

//vision sensors
extern Vision Police;
extern Vision EYES;

//Imu
extern Imu Vincent;

//Odom
extern ADIEncoder leftOdom;
extern ADIEncoder rightOdom;

//pots
extern ADIAnalogIn TeamColor;
extern ADIAnalogIn AutonNumber;

//line trackers
extern ADIAnalogIn IntakeSense;
extern ADIAnalogIn outtakeSense;
