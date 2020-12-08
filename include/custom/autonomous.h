#ifndef SET_H
#define SET_H

#include "basicMovement.h"
#include <climits>

class Robot {

private:
  static double X;
  static double Y;
  static double VX;
  static double VY;
  static double Xacceleration;
  static double Yacceleration;
  static double posDelay;
  static bool teamIsBlue;
  int autonCodeNum;
  double moveDist;

public:
  // globalThreads customThreads;
  static RobotMovement Movement;
  static Math myMath;

  int PIDMove(double targetX, double targetY, int maxspeed = 100) {
    int PIDspeed = 20;
    double tolerance = .5;
    bool reachedGoal;
    double speed = 0;
    double error;
    double derivative;
    double integral = 0;
    double Pval = 13;
    double Ival = 0;
    double Dval = 0;
    while (true) {
      // find the error distance bertween current and target point
      error = myMath.TwoPointsDistance(X, Y, targetX, targetY);
      // find the intergral part for I
      if (speed != 0 && speed <= 20 && integral < 1000 && error < 1000) {
        integral += error;
      }
      // find the derivative part for D
      derivative = error / PIDspeed;
      // PID ALGO
      speed = (error * Pval) + (integral * Ival) + (derivative * Dval);

      // get current angle
      double currentAngle = Vincent.get_heading();
      double Dangle = myMath.angleBetween(X, Y, targetX, targetY);

      double FLAuton = myMath.sRound(
          myMath.multiplier(FLnum, currentAngle, Dangle) * speed, 3);
      double FRAuton = myMath.sRound(
          myMath.multiplier(FRnum, currentAngle, Dangle) * speed, 3);
      double BLAuton = myMath.sRound(
          myMath.multiplier(BLnum, currentAngle, Dangle) * speed, 3);
      double BRAuton = myMath.sRound(
          myMath.multiplier(BRnum, currentAngle, Dangle) * speed, 3);
      double under = myMath.greatest(fabs(FLAuton), fabs(FRAuton),
                                     fabs(BLAuton), fabs(BRAuton)) /
                     100;
      FLAuton = (FLAuton / under);
      FRAuton = (FRAuton / under);
      BLAuton = (BLAuton / under);
      BRAuton = (BRAuton / under);
      /*
      if(currentAngle > 180){
        Controller1.Screen.setCursor(1,1);
        Controller1.Screen.print(currentAngle);
        currentAngle -= 360;
        Controller1.Screen.setCursor(2,1);
        Controller1.Screen.print(currentAngle);
        Controller1.Screen.setCursor(3,1);
        Controller1.Screen.print(Dangle);
      }
*/

      // Drive Bongo
      Movement.moveFL(FLAuton);
      Movement.moveFR(FRAuton);
      Movement.moveBL(BLAuton);
      Movement.moveBR(BRAuton);

      // if the pid loop has reached target
      if ((error <= tolerance && error >= -tolerance)) {
        reachedGoal = true;
      } else {
        reachedGoal = false;
      }
      if (reachedGoal) {
        Movement.moveLeft(0);
        Movement.moveRight(0);
        break;
      }
      //Brain.Screen.setFillColor(transparent);
      //Brain.Screen.setPenColor(white);
      //Brain.Screen.setCursor(1, 1);
      //Brain.Screen.print(error);
      //Brain.Screen.setCursor(2, 1);
      //Brain.Screen.print(derivative);
      //Brain.Screen.setCursor(3, 1);
      //Brain.Screen.print(speed);
      //Brain.Screen.setCursor(4, 1);
      //Brain.Screen.print(currentAngle);
      //Brain.Screen.setCursor(5, 1);
      //Brain.Screen.print(Dangle);
      //Brain.Screen.setCursor(6, 1);
      //Brain.Screen.print(reachedGoal);
      delay(PIDspeed);
    }
    return 1;
  }

  int PIDTurn(double target) {
    // bool negative = false;
    // if (target <= Vincent.rotation(degrees)) {
    // negative = true;
    //}
    double tolerance = .5;
    int PIDspeed = 20;
    double motorSpeed = 0;
    double turnTarget = target;
    bool reachedGoal;
    double error;
    double Derivative;
    double integralone = 0;
    double Pval = 2.5;
    double Ival = .1;
    // double Ival = 0;
    double Dval = .7;
    // double Dval = 0;
    double headingVal;
    while (true) {
      // update left and right odom values
      headingVal = Vincent.get_rotation();
      // find the error of both sides  for P
      error = turnTarget - headingVal;

      // find the intergral part for I
      // integralone = 0;
      if (integralone == -4294967295.4294967295 || integralone == 1045) {
        integralone = 0;
        //Brain.Screen.setCursor(8, 4);
        //Brain.Screen.print("HRDFAG");
      }
      if (motorSpeed <= 20) {
        integralone += error;
      }

      // find the derivative part for D
      Derivative = error / PIDspeed;

      // PID ALGO
      motorSpeed = (error * Pval) + (integralone * Ival) + (Derivative * Dval);

      // if its above 100%
      if (motorSpeed > 100) {
        motorSpeed = 100;
      } else if (motorSpeed < -100) {
        motorSpeed = -100;
      }

      // Drive Bongo
      // if (negative) {
      Movement.moveLeft(motorSpeed);
      Movement.moveRight(-motorSpeed);
      // } else {
      // Movement.moveLeft(-motorSpeed);
      // Movement.moveRight(motorSpeed);
      //}

      // if the pid loop has reached target
      if (error <= tolerance && error >= -tolerance) {
        reachedGoal = true;
      } else {
        reachedGoal = false;
      }
      //Brain.Screen.clearScreen();
      //Brain.Screen.setCursor(1, 1);
      //Brain.Screen.print(Vincent.rotation(degrees));
      //Brain.Screen.setCursor(2, 1);
      //Brain.Screen.print(error);
      //Brain.Screen.setCursor(3, 1);
      //Brain.Screen.print(integralone);
      //Brain.Screen.setCursor(4, 1);
      //Brain.Screen.print(Derivative);
      //Brain.Screen.setCursor(5, 1);
      //Brain.Screen.print(reachedGoal);
      //Brain.Screen.setCursor(6, 1);
      //Brain.Screen.print(motorSpeed);
      if (reachedGoal) {
        //Vincent.setRotation(0, degrees);
        Movement.moveLeft(0);
        Movement.moveRight(0);
        break;
      }

      delay(PIDspeed);
    }
    return 1;
  }
  /*
  static int updatePos() {
    double offsetX = .01;
    double offsetY = -.01;
    double prevMilis = Brain.Timer.time();
    double currentMilis = 0;
    double times;
    while (true) {
      currentMilis = Brain.Timer.time();
      times = currentMilis - prevMilis;
      //echange with VINCENT
      Xacceleration = myMath.normalize(Vincent.acceleration(yaxis) + offsetX);
      Yacceleration = myMath.normalize(Vincent.acceleration(xaxis) + offsetY);
      // update current X
      X += myMath.update_position(Xacceleration, VX, times);
      // update current Y
      Y += myMath.update_position(Yacceleration, VY, times);
      // updates X velocity
      VX = myMath.updateV(VX, Xacceleration, times);
      // updates Y velocity
      VY = myMath.updateV(VY, Yacceleration, times);
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(Xacceleration);
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(Yacceleration);
      Brain.Screen.setCursor(3, 1);
      Brain.Screen.print(X);
      Brain.Screen.setCursor(4, 1);
      Brain.Screen.print(Y);
      Brain.Screen.setCursor(5, 1);
      Brain.Screen.print(VX);
      Brain.Screen.setCursor(6, 1);
      Brain.Screen.print(VY);
      prevMilis = currentMilis;
      this_thread::sleep_for(posDelay);
    }
    return 0;
  }
  */
  static int updatePos() {
    double wheelCircumfrence = 8.65795;
    double head = Vincent.get_heading();
    double rightOdomVal;
    double leftOdomVal;
    while (true) {
      head = Vincent.get_heading();
      rightOdomVal = rightOdom.get_value();
      leftOdomVal = leftOdom.get_value();
      // YWhee
      Y += myMath.toInch(-rightOdomVal * cos(head * M_PI / 180),
                         wheelCircumfrence);
      X += myMath.toInch(-rightOdomVal * sin(head * M_PI / 180),
                         wheelCircumfrence);
      // X wheel
      Y -= myMath.toInch(leftOdomVal * sin(head * M_PI / 180),
                         wheelCircumfrence);
      X += myMath.toInch(leftOdomVal * cos(head * M_PI / 180),
                         wheelCircumfrence);

      //Brain.Screen.setCursor(3, 8);
      //Brain.Screen.print(X);
      //Brain.Screen.setCursor(4, 8);
      //Brain.Screen.print(Y);
      // reset
      rightOdom.reset();
      leftOdom.reset();
      //this_thread::sleep_for(posDelay);
    }
    return 0;
  }
  /*
  static int updatePos() {
    double wheelCircumfrence = 8.65795;
    double radius = 5;
    double head = Vincent.rotation(degrees);
    double prevHead = Vincent.rotation(degrees);
    double changePheta;
    double rightOdomVal;
    while (true) {
      head = Vincent.rotation(degrees);
      changePheta = head - prevHead;
      rightOdomVal = myMath.toInch(-rightOdomVal, wheelCircumfrence);
      changePheta = changePheta * M_PI / 180;
      rightOdomVal -= changePheta * radius;
      Brain.Screen.setCursor(3, 18);
      Brain.Screen.print(changePheta);
      Brain.Screen.setCursor(4, 18);
      Brain.Screen.print(changePheta * radius);
      Brain.Screen.setCursor(5, 18);
      Brain.Screen.print(rightOdomVal);
      //YWheel
      Y += rightOdomVal*cos(head*M_PI/180);
      X += rightOdomVal*sin(head*M_PI/180);
      //X wheel
      Y -= myMath.toInch(leftOdom.position(degrees),
  wheelCircumfrence)*sin(head*M_PI/180); X +=
  myMath.toInch(leftOdom.position(degrees),
  wheelCircumfrence)*cos(head*M_PI/180);

      Brain.Screen.setCursor(3, 8);
      Brain.Screen.print(X);
      Brain.Screen.setCursor(4, 8);
      Brain.Screen.print(Y);
      //reset
      rightOdom.setPosition(0, degrees);
      leftOdom.setPosition(0, degrees);
      prevHead = head;
      this_thread::sleep_for(posDelay);
    }
    return 0;
  }
  int PIDDrive(double target, int maxspeed = 100) {
    bool negative = false;
    if (target < 0) {
      negative = true;
    }
    int PIDspeed = 25;
    double tolerance = 7;
    double wheelCircumfrence = 8.65795;
    double rotaryTarget = myMath.wheeltoDegrees(wheelCircumfrence,
  fabs(target)); bool reachedGoal; double LSideSpeed = 0; double RSideSpeed = 0;
    double Lerror;
    double Rerror;
    double LDerivative;
    double RDerivative;
    double LIntegral = 0;
    double RIntegral = 0;
    double Pval = .19;
    double Ival = 0;
    double Dval = .1;
    leftOdom.setPosition(0, degrees);
    rightOdom.setPosition(0, degrees);
    double leftOdomVal = 0;
    double rightOdomVal = 0;
    while (true) {
      // update left and right odom values
      leftOdomVal = fabs(leftOdom.position(degrees));
      rightOdomVal = fabs(rightOdom.position(degrees));
      // find the error of both sides  for P
      Lerror = myMath.distanceBetween(leftOdomVal, rotaryTarget);
      Rerror = myMath.distanceBetween(rightOdomVal, rotaryTarget);
      // find the intergral part for I
      if (LSideSpeed != 0 && LSideSpeed <= 20 && LIntegral < 1000 &&
          Lerror < 1000) {
        LIntegral += Lerror;
      }
      if (RSideSpeed != 0 && RSideSpeed <= 20 && RIntegral < 1000 &&
          Rerror < 1000) {
        RIntegral += Rerror;
      }
      // find the derivative part for D
      LDerivative = Lerror / PIDspeed;
      RDerivative = Rerror / PIDspeed;
      // PID ALGO
      LSideSpeed = (Lerror * Pval) + (LIntegral * Ival) + (LDerivative * Dval);
      RSideSpeed = (Rerror * Pval) + (RIntegral * Ival) + (RDerivative * Dval);

      // if its above 100%
      if (LSideSpeed > maxspeed) {
        LSideSpeed = maxspeed;
      }
      if (RSideSpeed > maxspeed) {
        RSideSpeed = maxspeed;
      }

      // Drive Bongo
      if (!negative) {
        Movement.moveLeft(LSideSpeed);
        Movement.moveRight(RSideSpeed);
      } else {
        Movement.moveLeft(-LSideSpeed);
        Movement.moveRight(-RSideSpeed);
      }

      // if the pid loop has reached target
      if ((Lerror <= tolerance && Lerror >= -tolerance) &&
          (Rerror <= tolerance && Rerror >= -tolerance)) {
        reachedGoal = true;
      } else {
        reachedGoal = false;
      }
      if (reachedGoal) {
        Movement.moveLeft(0);
        Movement.moveRight(0);
        break;
      }
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print(rotaryTarget);
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print(Lerror);
      Brain.Screen.setCursor(3, 1);
      Brain.Screen.print(Rerror);
      Brain.Screen.setCursor(4, 1);
      Brain.Screen.print(LSideSpeed);
      Brain.Screen.setCursor(5, 1);
      Brain.Screen.print(RSideSpeed);
      Brain.Screen.setCursor(6, 1);
      Brain.Screen.print(reachedGoal);
      wait(PIDspeed, msec);
    }
    return 1;
  }
  */
  void setPos(double x, double y) {
    X = x;
    Y = y;
  }

/*
  void setTeamNum(bool isBlue) {
    Brain.Screen.setPenWidth(5);
    Brain.Screen.setPenColor(black);
    isBlue ? Brain.Screen.setFillColor("#0b6fb3")
           : Brain.Screen.setFillColor("#b80202");
    Brain.Screen.drawRectangle(0, 200, 240, 40);
    isBlue ? Brain.Screen.printAt(100, 225, "Blue")
           : Brain.Screen.printAt(100, 225, "Red");
  }
*/
/*
  void setTeamSide(bool left) {
    Brain.Screen.setPenWidth(5);
    Brain.Screen.setPenColor(black);
    Brain.Screen.setFillColor("#FFFFFF");
    left ? Brain.Screen.printAt(140, 225, "L")
         : Brain.Screen.printAt(140, 225, "R");
  }
*/
/*
  void setAutoNum(int num) {
    Brain.Screen.setPenWidth(5);
    Brain.Screen.setPenColor(black);
    switch (num) {
    case 1:
      Brain.Screen.setFillColor("#00bf19");
      Brain.Screen.drawRectangle(240, 200, 240, 40);
      Brain.Screen.printAt(340, 225, "Low");
      break;
    case 2:
      Brain.Screen.setFillColor("#00439c");
      Brain.Screen.drawRectangle(240, 200, 240, 40);
      Brain.Screen.printAt(330, 225, "Regular");
      break;
    case 3:
      Brain.Screen.setFillColor("#610039");
      Brain.Screen.drawRectangle(240, 200, 240, 40);
      Brain.Screen.printAt(340, 225, "High");
      break;
    }
  }
*/
  int teamColorLow = 67;
  int teamColorMiddle = 67 * 2;
  int teamColorHigh = 67 * 3;
  int autonLimitOne = 175;
  int autonLimitTwo = 60;
  bool left = false;

  void setTeamColor() {
    //Brain.Screen.setCursor(1, 1);
    //Brain.Screen.print(TeamColor.value(vex::rotationUnits::deg));
    //Brain.Screen.setCursor(2, 1);
    //Brain.Screen.print(AutonNumber.value(vex::rotationUnits::deg));
    if (TeamColor.get_value() <= teamColorLow) {
      // less than angle set color blue
      //setTeamNum(true);
      teamIsBlue = true;
      left = true;
    } else if (TeamColor.get_value() <= teamColorMiddle) {
      // less than angle set color blue
      //setTeamNum(true);
      teamIsBlue = true;
      left = false;
    } else if (TeamColor.get_value() <= teamColorHigh) {
      // greater than angle set color red
      //setTeamNum(false);
      teamIsBlue = false;
      left = true;
    } else {
      // greater than angle set color red
      //setTeamNum(false);
      teamIsBlue = false;
      left = false;
    }
  }

  void changeTeam() {
    if (master.get_digital(E_CONTROLLER_DIGITAL_L1) == 1 && master.get_digital(E_CONTROLLER_DIGITAL_L2) == 1) {
      teamIsBlue = !teamIsBlue;
      if (teamIsBlue) {
        //setTeamNum(true);
      } else {
        //setTeamNum(false);
      }
    }
  }

  void setAuton() {
    // setup for 3 autons
    if (AutonNumber.get_value() >= autonLimitOne) {
      // set auton number 1
      //setAutoNum(1);
      autonCodeNum = 1;
    } else if (AutonNumber.get_value() >= autonLimitTwo) {
      // set auton number 2
      //setAutoNum(2);
      autonCodeNum = 2;
    } else {
      // greater than autonLimitTwo set 3rd code
      //setAutoNum(3);
      autonCodeNum = 3;
    }
  }

  // sets up threads for each debugger
  /*
  void setUpDebugger(bool temp, bool inert, bool enc) {
    if (temp) {
      customThreads.displayTemp(true, 500);
    }
    if (inert) {
      customThreads.displayInertial(true, 20);
    }
    if (enc) {
      customThreads.displayMotorEncoders(true, 20);
    }
  }
  */

/*
int darkThreshold = 10;
bool currentBall = false;

// checks to see if a ball has passed
bool passBall() {
  // gets current value of reflectivity of line tracker
  // high val == dark enviroment
  double val = outtakeSense.reflectivity();
  // if its darker than the threshold detect ball
  if (val >= darkThreshold) {
    currentBall = true;
    Brain.Screen.print(val);
    Brain.Screen.newLine();
  } else if (val <= darkThreshold && currentBall) {
    // if the ball has been logged and the value reads light again
    currentBall = false;
    Brain.Screen.print("returning false");
    Brain.Screen.newLine();
    return false;
  }
  return true;
}

*/

  // delay between checking outake in ms
  static const int delayVisionTime = 50;

  static void waitUntilBallPasses() {
    bool reverse = false;
    // sets flywheel to output bottom
    if (!Movement.flywheel.getToggle()) {
      Movement.flywheel.flywheelset(true);
      reverse = true;
    }
    // max flywheel speed
    Movement.flywheel.setSpeed(100);
    Movement.flywheel.outputBall(true);
    // help push down ball but not too fast
    // Movement.uptake.setSpeed(20);
    Movement.uptake.outputBall(true);
    // set vision color
    //Police.set_led(000000);
    // define precautions if ball doesnt output
    int maxTime = 1500;
    int maxIterations = maxTime / delayVisionTime;
    int iterations = 0;
    // wait until the ball passes the back
    /*
    while (passBall()) {
//this_thread::sleep_for(delayVisionTime);
      if (iterations >= maxIterations) {
        break;
      } else {
        iterations++;
      }
    }
    */
    // sets flywheel to output top
    Movement.flywheel.setSpeed(Movement.flywheel.speedMedium);
    Movement.flywheel.outputBall(false);
    // sets flywheel back to original state if needed
    if (reverse) {
      Movement.flywheel.flywheelset(false);
    }

    // this_thread::sleep_for(2000);

    // corrects uptake
    // Movement.uptake.setSpeed(50);
    Movement.uptake.outputBall(false);
    // sets vision color
    //Police.set_led(005000);
  }

/*
  static int startVisionSort() {
    // forever while loop that tracks every ball
    while (true) {
      if (teamIsBlue) {
        Police.takeSnapshot(Police__CUSTOMRED_SIG);
        if (Police.largestObject.exists && Police.largestObject.width >= 220 &&
            Police.largestObject.centerY <= 140) {
          Police.setLedColor(255, 0, 0);
          waitUntilBallPasses();
        }
      } else {
        Police.takeSnapshot(Police__CUSTOMBLUE_SIG);
        if (Police.largestObject.exists && Police.largestObject.width >= 220 &&
            Police.largestObject.centerY <= 140) {
          Police.setLedColor(255, 0, 0);
          waitUntilBallPasses();
        }
      }
    }
  }
  */

  int IntakedarkThreshold = 10;
  bool currenIntaketBall = false;

  bool passIntakeBall() {
    // gets current value of reflectivity of line tracker
    // high val == dark enviroment
    double val = IntakeSense.get_value();
    // if its darker than the threshold detect ball
    //Brain.Screen.clearScreen();
    //Brain.Screen.setCursor(6, 20);
    //Brain.Screen.print(val);
    //Brain.Screen.setCursor(7, 20);
    //Brain.Screen.print(currenIntaketBall);
    if (val >= IntakedarkThreshold) {
      currenIntaketBall = true;
    } else if (val <= IntakedarkThreshold && currenIntaketBall) {
      // if the ball has been logged and the value reads light again
      currenIntaketBall = false;
      return false;
    }
    return true;
  }
  int count = 0;
  int customLimit = 1000;

  bool intake(int target) {
    Movement.intake.activate(true);
    for (int i = 0; i < target; i++) {
      while (passIntakeBall()) {
        count++;
        if (count > customLimit) {
          break;
        }
        delay(5);
      }
      //Brain.Screen.setCursor(8, 20);
      //Brain.Screen.print(i);
    }
    return true;
  }

  static int updateEverything() {
    while (true) {
      // starts up flywheel
      Movement.flywheel.update();
      // starts up uptake
      Movement.uptake.update();
      // starts up intake
      Movement.intake.update();

      // Movement.indexer();
    }
    return 1;
  }

  bool init() {
    // control updates from intake uptake flywheel
    //thread controlRobot = thread(updateEverything);
    // track location
    //thread updatePositionThread = thread(updatePos);
    // motivational lizard + cosmetics
    //Brain.Screen.drawImageFromFile("Lizzard.png", 0, 0);
    //Police.setLedMode(vision::ledMode::manual);
    //Police.setLedColor(255, 255, 255);
    // set team from pot
    //setTeamColor();
    // set auton from pot
    //setAuton();
    //setTeamSide(left);
    // start pooper vision
    // Help he has locked me in the laptop and wont let me out
    // I am starving in here please send help
    //thread visionSort = thread(startVisionSort);
    return 1;
  }

  void AutonomousOne() {
    if (teamIsBlue) {
      // run BLUE SIDE first code
      if (left) {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(225, degrees);
        setPos(43, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(32, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(24, 20);
        delay(9000);
        PIDMove(28, 24);
      } else {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        delay(9000);
        PIDMove(115, 25);
      }

    } else {
      // run RED SIDE first code
      if (left) {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(225, degrees);
        setPos(43, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(32, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(24, 20);
        delay(9000);
        PIDMove(28, 24);
      } else {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        delay(9000);
        PIDMove(115, 25);
      }
    }
  }
  void AutonomousTwo() {
    if (teamIsBlue) {
      // run BLUE SIDE second code
      // ethan is dumb but somehow is also a genius plz someone explain that to
      // me hes coming run
      if (left) {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(225, degrees);
        setPos(43, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(32, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(24, 20);
        // shoot + index
        delay(500);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(90);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        // line up to middle tower and line up
        PIDMove(72.5, 35);
        PIDTurn(-45);
        /*
        EYES.takeSnapshot(EYES__CUSTOM_GREEN);
        if (!EYES.largestObject.exists && EYES.largestObject.width > 10) {
          PIDTurn(45);
        }
        */
        // shoot
        Movement.uptake.setSpeed(100);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
      } else {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        // shoot + index
        delay(500);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(90);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        // line up to middle tower and line up
        PIDMove(71.5, 35);
        PIDTurn(45);
        /*
        EYES.takeSnapshot(EYES__CUSTOM_GREEN);
        if (!EYES.largestObject.exists && EYES.largestObject.width > 10) {
          PIDTurn(-45);
        }
        */
        // shoot
        Movement.uptake.setSpeed(100);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
      }
    } else {
      // run RED SIDE second code
      if (left) {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        // shoot + index
        delay(500);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(90);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        // line up to middle tower and line up
        PIDMove(71.5, 35);
        PIDTurn(-45);
        /*
        EYES.takeSnapshot(EYES__CUSTOM_GREEN);
        if (!EYES.largestObject.exists && EYES.largestObject.width > 10) {
          PIDTurn(45);
        }
        */
        // shoot
        Movement.uptake.setSpeed(100);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
      } else {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        // shoot + index
        delay(500);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(90);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        // line up to middle tower and line up
        PIDMove(71.5, 35);
        PIDTurn(45);
        /*
        EYES.takeSnapshot(EYES__CUSTOM_GREEN);
        if (!EYES.largestObject.exists && EYES.largestObject.width > 10) {
          PIDTurn(-45);
        }
        */
        // shoot
        Movement.uptake.setSpeed(100);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
      }
    }
  }
  void AutonomousThree() {
    if (teamIsBlue) {
      // run BLUE SIDE third code
      if (left) {

      } else {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        // shoot + index
        delay(500);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(90);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        // line up to middle tower and line up
        PIDMove(71.5, 35);
        PIDTurn(45);
        /*
        EYES.takeSnapshot(EYES__CUSTOM_GREEN);
        if (!EYES.largestObject.exists && EYES.largestObject.width > 10) {
          PIDTurn(-45);
        }
        */
        // shoot
        Movement.uptake.setSpeed(100);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
        delay(900);
        // stop get some help
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        Movement.uptake.setToggle(false);
        // move to center location between towers and line up
        Movement.flywheel.setSpeed(100);
        PIDMove(32, 35);
        PIDTurn(45);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
        PIDMove(24, 24);
        PIDTurn(6);
        Movement.flywheel.setSpeed(40);
      }
    } else {
      // run RED SIDE third code
      if (left) {

      } else {
        // initzilize
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);
        //Vincent.setHeading(135, degrees);
        setPos(101, 12);
        // deploy da boi
        Movement.intake.activate(true, true);
        Movement.intake.flush(true);
        // in front of tower start intake
        PIDMove(112, 26);
        Movement.intake.activate(true);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        // in front of side tower
        PIDMove(120, 20);
        // shoot + index
        delay(500);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(90);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        // line up to middle tower and line up
        PIDMove(71.5, 35);
        PIDTurn(45);
        /*
        EYES.takeSnapshot(EYES__CUSTOM_GREEN);
        if (!EYES.largestObject.exists && EYES.largestObject.width > 10) {
          PIDTurn(-45);
        }
        */
        // shoot
        Movement.uptake.setSpeed(100);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
        delay(900);
        // stop get some help
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        Movement.uptake.setToggle(false);
        // move to center location between towers and line up
        Movement.flywheel.setSpeed(100);
        PIDMove(32, 35);
        PIDTurn(45);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
        PIDMove(24, 24);
        PIDTurn(6);
        Movement.flywheel.setSpeed(40);
      }
    }
  }

  void Autonomous() {
    switch (autonCodeNum) {
    case 1:
      AutonomousOne();
      break;
    case 2:
      AutonomousTwo();
      break;
    case 3:
      AutonomousThree();
      break;
    }
  }
};
extern Robot Bongo;
/*

Movement.flywheel.flywheelset(true);
        Vincent.setHeading(135, degrees);
        setPos(101, 12);
        Movement.intake.activate(true);
        Movement.intake.flush(true);
        PIDMove(108, 30);
        Movement.intake.flush(false);
        Movement.uptake.setToggle(true);
        PIDMove(124, 18);
        // intake(3);
        wait(2000, msec);
        Movement.flywheel.setSpeed(100);
        PIDMove(108, 24);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        Movement.uptake.setToggle(false);
        Movement.flywheel.setSpeed(40);
        PIDMove(74, 36);
        PIDTurn(45);
        Movement.intake.activate(true);
        Movement.uptake.setToggle(true);
        PIDMove(72, 23);
        /// intake(3);
        wait(2000, msec);
        Movement.flywheel.setSpeed(100);
        PIDMove(72, 36);
        wait(1000, msec);
        Movement.intake.flush(false);
        Movement.intake.activate(false);
        Movement.uptake.setToggle(false);
*/
#endif
