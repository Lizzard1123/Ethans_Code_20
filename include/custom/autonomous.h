#ifndef AUTON
#define AUTON

#include "basicMovement.h"
#include <climits>

class Robot
{
private:
  // global X pos of bongo declared in global.cpp
  static double X;
  // global Y pos of bongo declared in global.cpp
  static double Y;
  // global position update delay for bongo declared in global.cpp
  static const double posDelay;
  // global team color of bongo declared in global.cpp
  static bool teamIsBlue;
  // auton selector num
  int autonCodeNum;
  // bongo has been initialized
  bool initz = false;
  // true if bongo is on left for auton
  bool left = false;
  // threshold for detecting ball passing through back
  static const int IntakedarkThreshold = 10;
  // delay between checking outake in ms
  static const int delayVisionTime = 50;

public:
  /*robot subsytems*/
  // class handler for movement + other funtions
  static RobotMovement Movement;
  // custom math reference
  static Math myMath;

  // sets team color to red
  void setRed()
  {
    teamIsBlue = false;
  }

  // sets team color to blue
  void setBlue()
  {
    teamIsBlue = true;
  }

  // sets auton number
  void setAutonNum(int num)
  {
    autonCodeNum = num;
  }

  // sets auton side, true is left
  void sideIsLeft(bool yes)
  {
    left = yes;
  }

  // returns true if team is blue
  bool getColor()
  {
    return teamIsBlue;
  }

  // returns auton num
  int getAutonNum()
  {
    return autonCodeNum;
  }

  // returns if bongo is on left during auton
  bool getSide()
  {
    return left;
  }

  // PID syncronous movement from current location to target X , Y set speed along the way
  int PIDMove(double targetX, double targetY, int maxspeed = 100)
  {
    // in ms
    int PIDspeed = 20;
    // tolerance in inches
    double tolerance = .5;
    bool reachedGoal;
    double speed = 0;
    double error;
    double derivative;
    double integral = 0;
    double Pval = 13;
    double Ival = 0;
    double Dval = 0;

    while (true)
    {
      // find the error distance bertween current and target point
      error = myMath.TwoPointsDistance(X, Y, targetX, targetY);

      // find the intergral part for I
      if ((speed != 0) && (speed <= 20) && (integral < 1000) && (error < 1000))
      {
        integral += error;
      }

      // find the derivative part for D
      derivative = error / PIDspeed;

      // PID ALGO
      speed = (error * Pval) + (integral * Ival) + (derivative * Dval);

      // get current angle
      double currentAngle = Vincent.get_heading();
      double Dangle = myMath.angleBetween(X, Y, targetX, targetY);

      // fancy algo
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

      // Drive Bongo
      Movement.moveFL(FLAuton);
      Movement.moveFR(FRAuton);
      Movement.moveBL(BLAuton);
      Movement.moveBR(BRAuton);

      // if the pid loop has reached target
      if (((error <= tolerance) && (error >= -tolerance)))
      {
        reachedGoal = true;
      }
      else
      {
        reachedGoal = false;
      }

      if (reachedGoal)
      {
        Movement.moveLeft(0);
        Movement.moveRight(0);
        break;
      }

      delay(PIDspeed);
    }
    return 1;
  }

  // PID syncronous turning TODO merge with movement
  int PIDTurn(double target)
  {
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

    while (true)
    {
      // update left and right odom values
      headingVal = Vincent.get_rotation();

      // find the error of both sides  for P
      error = turnTarget - headingVal;

      // find the intergral part for I
      // integralone = 0;
      if ((integralone == -4294967295.4294967295) || (integralone == 1045))
      {
        integralone = 0;
      }

      if (motorSpeed <= 20)
      {
        integralone += error;
      }

      // find the derivative part for D
      Derivative = error / PIDspeed;

      // PID ALGO
      motorSpeed = (error * Pval) + (integralone * Ival) + (Derivative * Dval);

      // if its above 100%
      if (motorSpeed > 100)
      {
        motorSpeed = 100;
      }
      else if (motorSpeed < -100)
      {
        motorSpeed = -100;
      }

      // Drive Bongo
      // if (negative) {
      Movement.moveLeft(motorSpeed);
      Movement.moveRight(-motorSpeed);

      // if the pid loop has reached target
      if ((error <= tolerance) && (error >= -tolerance))
      {
        reachedGoal = true;
      }
      else
      {
        reachedGoal = false;
      }

      if (reachedGoal)
      {
        // Vincent.setRotation(0, degrees);
        Movement.moveLeft(0);
        Movement.moveRight(0);
        break;
      }

      delay(PIDspeed);
    }
    return 1;
  }

  //update bongo current pos
  static void updatePos(void *)
  {
    /*
    TODO
    reduce movement whilst turning
    */
    double wheelCircumfrence = 8.65795;
    double head = Vincent.get_rotation();
    double rightOdomVal;
    double leftOdomVal;
    //0.055
    double radius = 3.12;
    double prev = 0;
    double tolerance = 0.01;
    while (true)
    {
      if (isnan(X))
      {
        X = 0;
      }
      if (isnan(Y))
      {
        Y = 0;
      }
      head = Vincent.get_rotation();
      double changePheta = (head - prev);
      double correction = ((changePheta < tolerance) ? 0 : changePheta) * radius;
      double initialVal = -rightOdom.get() - correction;
      rightOdomVal = myMath.toInch(initialVal, wheelCircumfrence);
      //printf("h %f \n", head);
      //printf("P %f \n", prev);
      //printf("CP %f \n", changePheta);
      //printf("c %f  \n", correction);
      //printf("i %f  \n", initialVal);
      //printf("v %f \n", rightOdomVal);

      leftOdomVal = leftOdom.get();

      // YWhee
      Y += rightOdomVal * cos(head * M_PI / 180);
      X += rightOdomVal * sin(head * M_PI / 180);

      // X wheel
      Y -= myMath.toInch(leftOdomVal * sin(head * M_PI / 180),
                         wheelCircumfrence);
      X += myMath.toInch(leftOdomVal * cos(head * M_PI / 180),
                         wheelCircumfrence);
      //debug

      // reset
      prev = head;
      rightOdom.reset();
      leftOdom.reset();
      c::task_delay(posDelay);
    }
  }


  // set current position of bongo
  void setPos(double x, double y)
  {
    X = x;
    Y = y;
  }

  // prints to debug screen current position of bongo
  void debugPos()
  {
    std::string xPos = "X: " + std::to_string(X);
    std::string yPos = "Y: " + std::to_string(Y);
    lv_label_set_text(debugXLabel, xPos.c_str());
    lv_label_set_text(debugYLabel, yPos.c_str());

    //printf("current x %f \n", X);
    //printf("current y %f \n", Y);
    //delay(1000);
  }

  // checks to see if a ball has passed TODO make async
  static bool passBall()
  {
    // define precautions if ball doesnt output
    int maxTime = 1500; //time in ms before shutoff
    int maxIterations = maxTime / delayVisionTime;
    int iterations = 0;
    const int darkThreshold = 2700;
    bool currentBall = false;

    while (true)
    {
      // gets current value of reflectivity of line tracker
      // high val == light enviroment
      double val = outtakeSense.get_value();

      if (iterations >= maxIterations)
      {
        break;
      }
      else
      {
        iterations++;
      }
      
      //sensor is dark, ball is there
      if (val <= darkThreshold)
      {
        currentBall = true;
      }
      else if (val >= darkThreshold && currentBall)
      {
        // if the ball has been logged and the value reads light again
        currentBall = false;
        return false;
      }
    }

    delay(delayVisionTime);
  }
  
  //handler for the outake process
  static void waitUntilBallPasses()
  {
    bool reverse = false;

    // sets flywheel to output bottom
    if (!Movement.flywheel.getToggle())
    {
      Movement.flywheel.flywheelset(true);
      reverse = true;
    }

    //uptake has to go down to output now
    Movement.uptake.setSpeed(30);
    Movement.uptake.flush(true);

    // max flywheel speed
    Movement.flywheel.setSpeed(100);
    Movement.flywheel.outputBall(true);

    // wait until the ball passes the back
    passBall();

    // sets flywheel to output top
    Movement.flywheel.setSpeed(Movement.flywheel.speedMedium);
    Movement.flywheel.outputBall(false);

    // sets flywheel back to original state if needed
    if (reverse)
    {
      Movement.flywheel.flywheelset(false);
    }

    // corrects uptake
    Movement.uptake.setSpeed(Movement.uptake.getSpeed());
    Movement.uptake.flush(false);
  }

  //handle outake checking
  static void handleOutake(void *)
  {
    // printf("here");
    if (Police.get_proximity() < 100)
    {
      printf("triggered");
      waitUntilBallPasses();
    }
    c::task_delay(15);
  }

  // change current team (swap) pressing L1 and L2 at same time when called
  void changeTeam()
  {
    if ((master.get_digital(E_CONTROLLER_DIGITAL_L1)) &&
        (master.get_digital(E_CONTROLLER_DIGITAL_L2)))
    {
      teamIsBlue = !teamIsBlue;
    }
  }


  //calls upon subsystems and updates them
  static void updateEverything(void *)
  {
    while (true)
    {
      // updates flywheel
      Movement.flywheel.update();
      // updates uptake
      Movement.uptake.update();
      // updates intake
      Movement.intake.update();
      c::task_delay(10);
    }
  }

  //returns true if bongo has initialized
  bool isinit()
  {
    return initz;
  }

  //starts up threads
  void initThreads()
  {
    // control updates from intake uptake flywheel
    Task control(updateEverything, nullptr, TASK_PRIORITY_DEFAULT,
                 TASK_STACK_DEPTH_DEFAULT, "control");

    // track location
    Task updatePosition(updatePos, nullptr, TASK_PRIORITY_DEFAULT,
                        TASK_STACK_DEPTH_DEFAULT, "updatePos");

    //handler for outake 
    Task sort(handleOutake, nullptr, TASK_PRIORITY_DEFAULT,
              TASK_STACK_DEPTH_DEFAULT, "sort");
    initz = true;
  }

/*

 AUTON MESS

*/
  void AutonomousOne()
  {
    if (teamIsBlue)
    {
      // run BLUE SIDE first code
      if (left)
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(225, degrees);
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
      }
      else
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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
    else
    {
      // run RED SIDE first code
      if (left)
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(225, degrees);
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
      }
      else
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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

  void AutonomousTwo()
  {
    if (teamIsBlue)
    {
      // run BLUE SIDE second code
      // ethan is dumb but somehow is also a genius plz someone explain that to
      // me hes coming run
      if (left)
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(225, degrees);
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
      }
      else
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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
    else
    {
      // run RED SIDE second code
      if (left)
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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
      }
      else
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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

  void AutonomousThree()
  {
    if (teamIsBlue)
    {
      // run BLUE SIDE third code
      if (left)
      {
      }
      else
      {
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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
    else
    {
      // run RED SIDE third code
      if (left)
      {
      }
      else
      {
        // initzilize
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(70);

        // Vincent.setHeading(135, degrees);
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

  void Autonomous()
  {
    switch (autonCodeNum)
    {
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

#endif // ifndef AUTON
