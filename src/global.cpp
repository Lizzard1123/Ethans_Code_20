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
Vision Police(20);
Vision EYES(9);

// Imu
Imu Vincent(8);

// Odom
ADIEncoder leftOdom('C', 'D');
ADIEncoder rightOdom('G', 'H');

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

double Robot::X = 0;
double Robot::Y = 0;

/*
   double Robot::VX = 0;
   double Robot::VY = 0;
   double Robot::Xacceleration = 0;
   double Robot::Yacceleration = 0;
 */
double Robot::posDelay = 20;
