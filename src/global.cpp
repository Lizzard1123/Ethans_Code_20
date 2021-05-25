#include "custom/autonomous.h"

// motors
Motor FL(FLPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor FR(FRPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor BL(BLPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor BR(BRPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor LArm(LArmPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor RArm(RArmPort, E_MOTOR_GEARSET_36, false, E_MOTOR_ENCODER_DEGREES);
Motor Flywheel(FlywheelPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
Motor Lift(LiftPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

// controllers
Controller master(E_CONTROLLER_MASTER);

// vision sensors
Vision EYES(EYESPort);
Vision Big_Brother(Big_BrotherPort);

//sigs
vision_signature_s_t EYES__CUSTOM_GREEN = Vision::signature_from_utility(EYES__CUSTOM_GREEN_NUM, -4949, -4509, -4729, -5669, -5035, -5352, 9.400, 0);
//vision_signature_s_t EYES__CUSTOM_GREEN = Vision::signature_from_utility(EYES__CUSTOM_GREEN_NUM, -3789, -3137, -3464, -5845, -5055, -5450, 2.5, 0);
//sigs two
/*

*/
vision_signature_s_t Big_Brother_CUSTOMBLUE_SIG = Vision::signature_from_utility(Big_Brother_CUSTOMBLUE_SIG_NUM, -2849, -1711, -2280, 7819, 12369, 10094, 3.000, 0);
vision_signature_s_t Big_Brother_CUSTOMRED_SIG = Vision::signature_from_utility(Big_Brother_CUSTOMRED_SIG_NUM, 7141, 9513, 8327, -799, 1, -399, 3.000, 0);

//Optical sensor
Optical Police(PolicePort);
Optical outtakeSense(outtakeSensePort);

//LED
ADIDigitalOut led('F', 1);

//pots
ADIAnalogIn rightArm(8);
ADIAnalogIn leftArm(7);

// Odom
okapi::ADIEncoder  leftOdom('e', 'f', false);
okapi::ADIEncoder  rightOdom('a', 'b', false);
okapi::ADIEncoder  middleOdom('c', 'd', true);

// Staic defines
RobotMovement Robot::Movement;
Math Robot::myMath;
bool Robot::teamIsBlue = false;
bool Robot::ballToggle = false;
const int Robot::delayVisionTime = 50;
const int Robot::IntakedarkThreshold; 
const double Robot::posDelay = 20;

double Robot::X = 0;
double Robot::Y = 0;
double Robot::thisRotation = 0;


//20