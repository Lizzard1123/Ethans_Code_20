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
#include "custom/autonomous.h"

// motors
Motor FL(FLPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor FR(FRPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor BL(BLPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor BR(BRPort, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor LArm(LArmPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor RArm(RArmPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor Flywheel(FlywheelPort, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_DEGREES);
Motor Lift(LiftPort, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);

// controllers
Controller master(E_CONTROLLER_MASTER);

// vision sensors
Vision EYES(EYESPort);
Vision Big_Brother(Big_BrotherPort);

//sigs
vision_signature_s_t EYES__CUSTOM_GREEN = Vision::signature_from_utility(EYES__CUSTOM_GREEN_NUM, -3789, -3137, -3464, -5845, -5055, -5450, 2.5, 0);

//sigs two
vision_signature_s_t Big_Brother_CUSTOMBLUE_SIG = Vision::signature_from_utility(Big_Brother_CUSTOMBLUE_SIG_NUM, -2849, -1711, -2280, 7819, 12369, 10094, 3.000, 0);
vision_signature_s_t Big_Brother_CUSTOMRED_SIG = Vision::signature_from_utility(Big_Brother_CUSTOMRED_SIG_NUM, 7141, 9513, 8327, -799, 1, -399, 3.000, 0);

//Optical sensor
Optical Police(PolicePort);

// Imu
Imu Vincent(IMUPort);

// Odom
okapi::ADIEncoder  leftOdom('c', 'd', false);
okapi::ADIEncoder  rightOdom('g', 'h', false);

// pots
ADIAnalogIn TeamColor('F');
ADIAnalogIn AutonNumber('E');

// line trackers
ADIAnalogIn IntakeSense('A');
ADIAnalogIn outtakeSense('B');

// Staic defines
RobotMovement Robot::Movement;
Math Robot::myMath;
bool Robot::teamIsBlue;
const int Robot::delayVisionTime;
const int Robot::IntakedarkThreshold; 
const double Robot::posDelay = 1000;

double Robot::X = 0;
double Robot::Y = 0;

/*
   double Robot::VX = 0;
   double Robot::VY = 0;
   double Robot::Xacceleration = 0;
   double Robot::Yacceleration = 0;
 */


//20