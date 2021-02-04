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
#define LArmPort 6
#define RArmPort 18
#define FlywheelPort 7
#define LiftPort 3
#define PolicePort 20
#define EYESPort 9
#define Big_BrotherPort 5
#define IMUPort 8
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
extern Vision EYES;
extern Vision Big_Brother;

//sigs
#define EYES__CUSTOM_GREEN_NUM 1
#define Big_Brother_CUSTOMRED_SIG_NUM 1
#define Big_Brother_CUSTOMBLUE_SIG_NUM 2

extern vision_signature_s_t  Big_Brother_CUSTOMRED_SIG;
extern vision_signature_s_t  Big_Brother_CUSTOMBLUE_SIG;
extern vision_signature_s_t  EYES__CUSTOM_GREEN;

//opical sensor
extern Optical Police;

//Imu
extern Imu Vincent;

//Odom
extern okapi::ADIEncoder  leftOdom;
extern okapi::ADIEncoder  rightOdom;

//pots
extern ADIAnalogIn TeamColor;
extern ADIAnalogIn AutonNumber;

//line trackers
extern ADIAnalogIn IntakeSense;
extern ADIAnalogIn outtakeSense;

//labels debug
extern lv_obj_t *debugXLabel;
extern lv_obj_t *debugYLabel;

//global teamcolor
extern bool teamIsBlue;

#endif

