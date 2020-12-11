#ifndef MOVE
#define MOVE
#include "global.h"
#include <climits>
#define FLnum 1
#define FRnum 2
#define BLnum 2
#define BRnum 1
const double G = 9.80665;
const double MTOINCH = 39.37;
class Math {
public:
  double toRPM(bool reverse, double speed, int gear){
    int check = (reverse) ? -1 : 1;
    int gearRatio = 10;
    switch(gear){
      case E_MOTOR_GEARSET_36:
        gearRatio = 100;
        //printf("Torq");
        break;
      case E_MOTOR_GEARSET_18:
        gearRatio = 200;
        //printf("Reg");
        break;
      case E_MOTOR_GEARSET_06:
        gearRatio = 600;
        //printf("Speed");
        break;
    }
    return check * (speed/100) * gearRatio;
  }
  // returns sum of all vals in array
  double sumOf(int length, double nums[]) {
    double total = 0;
    for (int i = 0; i < length; i++) {
      total += nums[i];
    }
    return total / length;
  }
  // params circumfrence of wheel, distance to go returns rotary pos of that
  // point
  double wheeltoDegrees(double cir, double dist) {
    return round((dist / cir) * 360);
  }
  // param current rotary position, target
  double distanceBetween(double curr, double target) { return target - curr; }
  // gets average of four num
  double getAverage(double one, double two, double three, double four) {
    double average = (one + two + three + four) / 4;
    return average;
  }

  double TwoPointsDistance(double xone, double yone, double xtwo, double ytwo) {
    double Xdifference = fabs((xone - xtwo));
    double Ydifference = fabs((yone - ytwo));
    return sqrt(pow(Xdifference, 2) + pow(Ydifference, 2));
  }

  double greatest(double FL, double FR, double BL, double BR) {
    if (FL >= 100 || FR >= 100 || BL >= 100 || BR >= 100) {
      double finalnum = FL;
      if (finalnum <= FR) {
        finalnum = FR;
      }
      if (finalnum <= BL) {
        finalnum = BL;
      }
      if (finalnum <= BR) {
        finalnum = BR;
      }
      if (finalnum != 0) {
        return finalnum;
      } else {
        return 100;
      }
    } else {
      return 100;
    }
  }
  double convert(double g) {
    double G = 9.80665;
    return G * g;
  }

  // new algos section
  // to degress from r
  double toDegrees(double r) { return (r * 180) / M_PI; }

  // returns rounded decimal place
  double sRound(double num, int decimal) {
    int mult = pow(10, decimal);
    return round(num * mult) / mult;
  }

  // returns slope, if denom is 0 then striaght line up, if numer is 0 then
  // slope of 0
  double slope(double Xone, double Yone, double Xtwo, double Ytwo) {
    if ((Xtwo - Xone) == 0) {
      return LONG_MAX;
    } else if ((Ytwo - Yone) == 0) {
      return 0;
    }
    return (Ytwo - Yone) / (Xtwo - Xone);
  }

  // takes in degress andd wheel circulmfrwenqslen and reuturns inches moved
  double toInch(double degrees, double wheelCircumfrence) {
    return degrees / 360 * wheelCircumfrence;
  }
  // returns if point is left of a line
  bool Left(double Xone, double Yone, double Xtwo, double Ytwo, double PX,
            double PY) {
    return ((PX - Xone) * (Ytwo - Yone) - (PY - Yone) * (Xtwo - Xone)) < 0;
  }

  // returns if points is right of line
  bool Right(double Xone, double Yone, double Xtwo, double Ytwo, double PX,
             double PY) {
    return ((PX - Xone) * (Ytwo - Yone) - (PY - Yone) * (Xtwo - Xone)) > 0;
  }

  // returns distance from point to line
  double findDistance(double thisSlope, double PX, double PY) {
    return fabs((-thisSlope * PX + PY)) / sqrt(1 + pow(thisSlope, 2));
  }

  // returns the wacky number depending on motor side
  double multiplier(int num, double cangle, double Dangle) {
    int check;
    switch (num) {
    case 1:
      // FL BR
      Dangle += 45;
      check = 1;
      break;
    case 2:
      // FR BL
      Dangle -= 45;
      check = -1;
      break;
    }
    double slopeLineX = sRound(sin(Dangle * M_PI / 180), 5);
    double slopeLineY = sRound(cos(Dangle * M_PI / 180), 5);
    double targetX = sRound(sin(cangle * M_PI / 180), 5);
    double targetY = sRound(cos(cangle * M_PI / 180), 5);
    double dist =
        findDistance(slope(0, 0, slopeLineX, slopeLineY), targetX, targetY);
    if (Left(0, 0, slopeLineX, slopeLineY, targetX, targetY)) {
      return check * dist;
    } else if (Right(0, 0, slopeLineX, slopeLineY, targetX, targetY)) {
      return -check * dist;
    }
    return dist;
  }

  // get new velocity
  double updateV(double Vo, double A, double T) {
    if (motorsNotMoving()) {
      return 0;
    }
    return Vo + A * (T / 1000);
  }
  // return the Acc in m/s^2
  bool motorsNotMoving() {
    return (FL.get_target_velocity() == 0) && (FR.get_target_velocity() == 0) &&
           (BL.get_target_velocity() == 0) && (BR.get_target_velocity() == 0);
  }
  double normalize(double acc) {
    if (acc < 0.01 && acc > -0.01) {
      return 0;
    }
    if (motorsNotMoving()) {
      return 0;
    }
    return acc * G;
  }
  // Input current accelartion and velocity
  // Outputs change in position
  double update_position(double accel, double velo, double timeinSec) {
    timeinSec /= 1000;
    return (timeinSec * velo + .5 * accel * pow(timeinSec, 2)) * MTOINCH;
  }

  double angleBetween(double X, double Y, double targetX, double targetY) {
    double Ydist = targetY - Y;
    double dist = TwoPointsDistance(X, Y, targetX, targetY);
    double check = 1;
    if (targetX < X) {
      check = -1;
    }
    double solution = acos(Ydist / dist) * 180 / M_PI * check;
    //Brain.Screen.setCursor(3, 10);
    //Brain.Screen.print(Ydist);
    //Brain.Screen.setCursor(4, 10);
    //Brain.Screen.print(dist);
    //Brain.Screen.setCursor(5, 10);
    //Brain.Screen.print(check);
    //Brain.Screen.setCursor(6, 10);
    //Brain.Screen.print(solution);
    return solution;
  }
};

class flywheelClass {
private:
  double flywheelspeed = 40;
  bool flywheeltoggle = false;
  bool currentOutputBall = false;

public:
  double speedLow = 50;
  double speedMedium = 45;
  double speedHigh = 100;
  Math myMath;
  // toggles flywheel
  void flywheeltoggleswitch() { flywheeltoggle = !flywheeltoggle; };
  void flywheelset(bool setting) { flywheeltoggle = setting; };
  // updates it
  void update() {
    if (flywheeltoggle) { // change flywheel % in double
      if (currentOutputBall) {
        Flywheel.move_velocity(myMath.toRPM(true, flywheelspeed, Flywheel.get_gearing()));
      } else {
        Flywheel.move_velocity(myMath.toRPM(false, flywheelspeed, Flywheel.get_gearing()));
      }
    } else { // idle
      Flywheel.move_velocity(0);
    }
  }
  bool getSpeed() { return flywheelspeed; }
  bool getToggle() { return flywheeltoggle; }
  void outputBall(bool setting) { currentOutputBall = setting; }
  void setSpeed(double speed) { flywheelspeed = speed; }
};

class intakeClass {
private:
  double intakespeed = 100;
  bool isflush = false;
  bool moving = false;
  bool opposite = false;
public:
  Math myMath;
  // stops intakes
  void stopBoth() {
    LArm.move_velocity(0);
    RArm.move_velocity(0);
  }
  void update() {
    //if moving and not flushing
    //spin intakes inward
    if (moving && !isflush) {
      //spins left opposite
      if(opposite){
        LArm.move_velocity(myMath.toRPM(true, intakespeed, LArm.get_gearing()));
      } else {
        LArm.move_velocity(myMath.toRPM(false, intakespeed, LArm.get_gearing()));
      }
      RArm.move_velocity(myMath.toRPM(true, intakespeed, RArm.get_gearing()));
    // if the intakes are flusing  reverse intakes
    } else if (isflush) {
      if(opposite){
        LArm.move_velocity(myMath.toRPM(false, intakespeed, LArm.get_gearing()));
      } else {
        LArm.move_velocity(myMath.toRPM(true, intakespeed, LArm.get_gearing()));
      }
      RArm.move_velocity(myMath.toRPM(false, intakespeed, RArm.get_gearing()));
    } else {
      stopBoth();
    }
  }
  void activate(bool setting, bool other = false) { moving = setting; opposite = other;}
  // sets flush
  void flush(bool setting) { isflush = setting; }
};

class uptakeClass {
private:
  int liftspeed = 50;
  bool toggled = false;
  bool isflush = false;
  bool output = false;

public:
  Math myMath;
  void stopBoth() { Lift.move_velocity(0); }
  void update() {
    if (output) {
      stopBoth();
    } else if (toggled && !isflush) {
      Lift.move_velocity(myMath.toRPM(true, liftspeed, Lift.get_gearing()));
    } else if (isflush) {
      Lift.move_velocity(myMath.toRPM(false, liftspeed, Lift.get_gearing()));
    } else {
      stopBoth();
    }
  }
  void setToggle(bool setting) { toggled = setting; }
  void outputBall(bool setting) { output = setting; }
  void toggle() { toggled = !toggled; }
  bool getToggle() { return toggled; }
  // sets flush
  void setSpeed(double setting) { liftspeed = setting; }
  void flush(bool setting) { isflush = setting; }
};
class RobotMovement {

private:
  // how much the encodervaleues change the speed
  // one means for every encoder value different add to speed
  double headingScale = .5;

  double LXaxis = 0;
  double LYaxis = 0;
  double RXaxis = 0;
  double RYaxis = 0;
  // experimental turn value down
  double tune = 1.5;
  double flushspeed = 60;
  bool currenttoggleState = false;

  // takes in inputs and makes final speed
  double FLspeed = LYaxis + LXaxis + RXaxis;
  double FRspeed = LYaxis - LXaxis - RXaxis;
  double BLspeed = LYaxis - LXaxis + RXaxis;
  double BRspeed = LYaxis + LXaxis - RXaxis;

  // porpotionate algorythm
  double under;

  // speed using arrows
  double cardinalspeed = 30;

public:
  // parts of the bot
  flywheelClass flywheel;
  intakeClass intake;
  uptakeClass uptake;
  Math myMath;
  // speedcontrol variables
  double mediummultiplier = .75;
  double regularmultiplier = 1;
  double slowmultiplier = .5;

  // true if negative
  bool upDirections[4] = {false, false, false, false};
  bool rightDirections[4] = {false, true, true, false};
  bool downDirections[4] = {true, true, true, true};
  bool leftDirections[4] = {true, false, false, true};

  double prevFLenc;
  double prevFRenc;
  double prevBLenc;
  double prevBRenc;

  // clears rotations for encoders
  void clearRotations() {
    c::motor_set_zero_position(FLPort, 0);
    c::motor_set_zero_position(FRPort, 0);
    c::motor_set_zero_position(BLPort, 0);
    c::motor_set_zero_position(BRPort, 0);
  }
  // neg right pos left
  double offset = -16;
  double error;
  double targetCX;
  double CX;
  double width;
  double Pval = .4;
  /*
  void lineUp() {
    EYES.takeSnapshot(EYES__CUSTOM_GREEN);
    if (EYES.largestObject.exists) {
      width = EYES.largestObject.width;
      // neg right pos left
      CX = EYES.largestObject.centerX;
      targetCX = -1.3286 * width + 140.619 + offset;
      error = CX - targetCX;
      FLspeed += Pval * error;
      FRspeed -= Pval * error;
      BLspeed += Pval * error;
      BRspeed -= Pval * error;
      //Brain.Screen.setCursor(1, 15);
      //Brain.Screen.print(width);
      //Brain.Screen.setCursor(2, 15);
      //Brain.Screen.print(CX);
      //Brain.Screen.setCursor(3, 15);
      //Brain.Screen.print(targetCX);
      //Brain.Screen.setCursor(4, 15);
      //Brain.Screen.print(error);
    } else {
      //Brain.Screen.setCursor(6, 12);
      //Brain.Screen.print("Fail");
    }
  }
*/
  // helper func that returns number of encoder pos away from average scaled
  // from global var
  double scale(double av, double part) { return (av - part) * headingScale; }
  double deadZone = 5;
  // moves in cardinal directions
  void cardinalMove(bool forward[]) {
    double FLcurrent = c::motor_get_position(FLPort);
    double FRcurrent = c::motor_get_position(FRPort);
    double BLcurrent = c::motor_get_position(BLPort);
    double BRcurrent = c::motor_get_position(BRPort);
    double average = myMath.getAverage(fabs(FLcurrent), fabs(FRcurrent),
                                       fabs(BLcurrent), fabs(BRcurrent));
    double FLscale = scale(average, fabs(FLcurrent));
    double FRscale = scale(average, fabs(FRcurrent));
    double BLscale = scale(average, fabs(BLcurrent));
    double BRscale = scale(average, fabs(BRcurrent));
    FLspeed =
        forward[0] ? -(cardinalspeed + FLscale) : (cardinalspeed + FLscale);
    FRspeed =
        forward[1] ? -(cardinalspeed + FRscale) : (cardinalspeed + FRscale);
    BLspeed =
        forward[2] ? -(cardinalspeed + BLscale) : (cardinalspeed + BLscale);
    BRspeed =
        forward[3] ? -(cardinalspeed + BRscale) : (cardinalspeed + BRscale);
    //delay(10);
  }
  // upadate controller vars for bongo orientation
  void catieControll() {
    LXaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_X));
    printf("LXaxis %f\n", LXaxis);
    LYaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    printf("LYaxis %f\n", LYaxis);
    RXaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) / tune;
    printf("RXaxis %f\n", RXaxis);
    RYaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

    FLspeed = RYaxis + RXaxis;
    FRspeed = RYaxis - RXaxis;
    BLspeed = RYaxis + RXaxis;
    BRspeed = RYaxis - RXaxis;

    // set speeds in order to move bongo in target agle taken into account
    // current angle
    if ((LXaxis > deadZone || LXaxis < -deadZone) ||
        (LYaxis > deadZone || LYaxis < -deadZone)) {
      // updates
      double speed = myMath.TwoPointsDistance(0, 0, LXaxis, LYaxis);
      // offset so it drives at 100% going forward
      // =speed *= 1.5;

      // find the angle between straight forward
      double Dangle = acos(LYaxis / speed) * 180 / M_PI;
      // negative if the x axis is on left or neg
      if (LXaxis < 0) {
        Dangle *= -1;
      }
      // current angle
      double currentAngle = Vincent.get_heading();
      FLspeed += myMath.sRound(
          myMath.multiplier(FLnum, currentAngle, Dangle) * speed, 3);
      FRspeed += myMath.sRound(
          myMath.multiplier(FRnum, currentAngle, Dangle) * speed, 3);
      BLspeed += myMath.sRound(
          myMath.multiplier(BLnum, currentAngle, Dangle) * speed, 3);
      BRspeed += myMath.sRound(
          myMath.multiplier(BRnum, currentAngle, Dangle) * speed, 3);
    }

    double under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                                   fabs(BRspeed)) /
                   100;
    FLspeed = (FLspeed / under);
    FRspeed = (FRspeed / under);
    BLspeed = (BLspeed / under);
    BRspeed = (BRspeed / under);
  }

  // upadate controller vars for bongo orientation
  void updateControllerAxis() {
      LXaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_X));
      LYaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
      RXaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) / tune;    // updates
    FLspeed = LYaxis + LXaxis + RXaxis;
    FRspeed = LYaxis - LXaxis - RXaxis;
    BLspeed = LYaxis - LXaxis + RXaxis;
    BRspeed = LYaxis + LXaxis - RXaxis;

    double under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                                   fabs(BRspeed)) /
                   100;
    FLspeed = (FLspeed / under);
    FRspeed = (FRspeed / under);
    BLspeed = (BLspeed / under);
    BRspeed = (BRspeed / under);
  }

  // upadate controller vars
  void moveRelative() {
    // current controller axis values in %
    LXaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_X) / 127 * 100);
    LYaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y) / 127 * 100);
    RXaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X) / 127 * 100) / tune;
    // speed is distance from 0
    double speed = myMath.TwoPointsDistance(0, 0, LXaxis, LYaxis);

    // offset so it drives at 100% going forward
    // speed *= 1.5;

    // find the angle between straight forward
    double Dangle = acos(LYaxis / speed) * 180 / M_PI;
    // negative if the x axis is on left or neg
    if (LXaxis < 0) {
      Dangle *= -1;
    }
    // current angle
    double currentAngle = Vincent.get_heading();

    // set speeds in order to move bongo in target agle taken into account
    // current angle
    FLspeed = myMath.sRound(
        myMath.multiplier(FLnum, currentAngle, Dangle) * speed, 3);
    FRspeed = myMath.sRound(
        myMath.multiplier(FRnum, currentAngle, Dangle) * speed, 3);
    BLspeed = myMath.sRound(
        myMath.multiplier(BLnum, currentAngle, Dangle) * speed, 3);
    BRspeed = myMath.sRound(
        myMath.multiplier(BRnum, currentAngle, Dangle) * speed, 3);

    // turn whilst doing so
    FLspeed += RXaxis;
    FRspeed -= RXaxis;
    BLspeed += RXaxis;
    BRspeed -= RXaxis;

    // proportion it all
    double under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                                   fabs(BRspeed)) /
                   100;

    FLspeed = (FLspeed / under);
    FRspeed = (FRspeed / under);
    BLspeed = (BLspeed / under);
    BRspeed = (BRspeed / under);
  }

  // alter the speed
  void alterSpeed(double speed) {
    under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                            fabs(BRspeed)) /
            100;
    FLspeed = (FLspeed / under) * speed;
    FRspeed = (FRspeed / under) * speed;
    BLspeed = (BLspeed / under) * speed;
    BRspeed = (BRspeed / under) * speed;
  }

  // drives motors from private vars
  void move() {
    FR.move_velocity(myMath.toRPM(false, FRspeed, FR.get_gearing()));
    //printf("FL %f\n", FLspeed);
    FL.move_velocity(myMath.toRPM(false, FLspeed, FL.get_gearing()));
    //printf("FR %f\n", FRspeed);
    BR.move_velocity(myMath.toRPM(false, BRspeed, BR.get_gearing()));
    //printf("BL %f\n", BLspeed);
    BL.move_velocity(myMath.toRPM(false, BLspeed, BL.get_gearing()));
    //printf("BR %f\n", BRspeed);
    //Brain.Screen.setCursor(6, 19);
    //Brain.Screen.print(FLspeed);
    //Brain.Screen.setCursor(7, 19);
    //Brain.Screen.print(FRspeed);
    //Brain.Screen.setCursor(8, 19);
    //Brain.Screen.print(BLspeed);
    //Brain.Screen.setCursor(9, 19);
    //Brain.Screen.print(BRspeed);
  }
  void moveLeft(double speed) {
    FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing()));
    BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing()));
  }

  void moveRight(double speed) {
    FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing()));
    BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing()));
  }

  void moveFL(double speed) { FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing())); }
  void moveFR(double speed) { FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing())); }
  void moveBL(double speed) { BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing())); }
  void moveBR(double speed) { BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing())); }

  // reverses motors to get a ball out front
  void flush(bool setting) {
    intake.flush(setting);
    uptake.flush(setting);
  }

  // stops all functions
  void stopAll() {
    intake.stopBoth();
    uptake.setToggle(false);
    flywheel.flywheelset(false);
  }
};
#endif
