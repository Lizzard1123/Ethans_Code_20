#ifndef GLOBAL
#define GLOBAL
#include "main.h"
#define FLPort 20
#define FRPort 16
#define BLPort 17
#define BRPort 18
#define LArmPort 1
#define RArmPort 13
#define FlywheelPort 7
#define LiftPort 19
#define PolicePort 14
#define EYESPort 10
#define Big_BrotherPort 6
#define IMUPort 8
#define outtakeSensePort 15
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
extern Optical outtakeSense;

//pots
extern ADIAnalogIn rightArm;
extern ADIAnalogIn leftArm;

//Imu
extern Imu Vincent;

//LED
extern ADIDigitalOut led;

//Odom
extern okapi::ADIEncoder  leftOdom;
extern okapi::ADIEncoder  rightOdom;

//pots
extern ADIAnalogIn TeamColor;
extern ADIAnalogIn AutonNumber;

//labels debug
extern lv_obj_t *debugXLabel;
extern lv_obj_t *debugYLabel;

//global teamcolor
extern bool teamIsBlue;

#endif

