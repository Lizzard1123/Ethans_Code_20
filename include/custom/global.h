#ifndef GLOBAL
#define GLOBAL
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
#define FLPort 4
#define FRPort 19
#define BLPort 2
#define BRPort 1
#define LArmPort 5
#define RArmPort 18
#define FlywheelPort 7
#define LiftPort 3
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
extern Controller master;

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

//vars
extern bool PREAUTON;
#endif
