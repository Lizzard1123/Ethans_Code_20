#ifndef AUTON
#define AUTON

#include "basicMovement.h"
#include <climits>

class Robot
{
private:
  static const double angleOffset;
  // global X pos of bongo declared in global.cpp
  static double X;
  // global Y pos of bongo declared in global.cpp
  static double Y;
  // global position update delay for bongo declared in global.cpp
  static const double posDelay;
  // global record position state declared in global.cpp
  static bool recordLocation;
  // global team color of bongo declared in global.cpp
  static bool teamIsBlue;
  //toggle for pooping
  static bool ballToggle;
  // auton selector num
  int autonCodeNum = 3;
  // bongo has been initialized
  bool initz = false;
  // true if bongo is on left for auton
  bool left = true;
  // threshold for detecting ball passing through back
  static const int IntakedarkThreshold = 10;
  // delay between checking outake in ms
  static const int delayVisionTime;

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

  //returns x variable
  double getX()
  {
    return X;
  }
  //returns y variable
  double getY()
  {
    return Y;
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
    int PIDspeed = 100;
    // tolerance in inches
    double tolerance = 1;
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
      double currentAngle = Vincent.get_rotation() + angleOffset;
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
      printf("FLAuton %f \n", FLAuton);
      printf("FRAuton %f \n", FRAuton);
      printf("BLAuton %f \n", BLAuton);
      printf("BRAuton %f  \n", BRAuton);
      printf("currentAngle %f  \n", currentAngle);
      printf("Dangle %f \n", Dangle);
      printf("error %f \n", error);
      printf("X:  %f \n", X);
      printf("Y:  %f \n", Y);
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
    recordLocation = false;
    double tolerance = .5;
    int PIDspeed = 10;
    double motorSpeed = 0;
    double turnTarget = target;
    bool reachedGoal;
    double error;
    double Derivative = 0;
    double integralone = 0;
    double Pval = 2.5;
    //double Ival = .1;

    // double Ival = 0;
    //double Dval = .7;
    double Ival = 0;
    double Dval = 0;

    // double Dval = 0;
    double headingVal;

    while (true)
    {
      // update left and right odom values
      headingVal = Vincent.get_rotation() + angleOffset;
      printf("Heading: %f", headingVal);

      // find the error of both sides  for P
      error = turnTarget - headingVal;

      // find the intergral part for I
      // integralone = 0;
      //if ((integralone == -4294967295.4294967295) || (integralone == 1045))
      //{
      //  integralone = 0;
      //}

      //if (motorSpeed <= 20)
      //{
      //  integralone += error;
      //}

      // find the derivative part for D
      //Derivative = error / PIDspeed;

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
        recordLocation = true;
        break;
      }

      delay(PIDspeed);
    }
    return 1;
  }

  //PID turnMove turns and moves
  int PIDMoveTurn(double targetX, double targetY, double target, int maxspeed = 100)
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

    double t_tolerance = .5;
    int t_PIDspeed = 20;
    double t_motorSpeed = 0;
    double t_turnTarget = target;
    bool t_reachedGoal;
    double t_error;
    double t_Derivative;
    double t_integralone = 0;
    double t_Pval = 2.5;
    double t_Ival = .1;
    // double Ival = 0;
    double t_Dval = .7;
    // double Dval = 0;
    double t_headingVal;

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
      double currentAngle = Vincent.get_heading() + angleOffset;
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

      /*
      TURNN
      */

      // update left and right odom values
      t_headingVal = Vincent.get_rotation() + angleOffset;

      // find the error of both sides  for P
      error = t_turnTarget - t_headingVal;

      // find the intergral part for I
      // integralone = 0;
      if ((t_integralone == -4294967295.4294967295) || (t_integralone == 1045))
      {
        t_integralone = 0;
      }

      if (t_motorSpeed <= 20)
      {
        t_integralone += t_error;
      }

      // find the derivative part for D
      t_Derivative = t_error / t_PIDspeed;

      // PID ALGO
      t_motorSpeed = (t_error * t_Pval) + (t_integralone * t_Ival) + (t_Derivative * t_Dval);

      // if its above 100%
      if (t_motorSpeed > 100)
      {
        t_motorSpeed = 100;
      }
      else if (t_motorSpeed < -100)
      {
        t_motorSpeed = -100;
      }

      // if the pid loop has reached target
      if ((t_error <= t_tolerance) && (t_error >= -t_tolerance))
      {
        t_reachedGoal = true;
      }
      else
      {
        t_reachedGoal = false;
      }

      // Drive Bongo
      Movement.moveFL(FLAuton + t_motorSpeed);
      Movement.moveFR(FRAuton + t_motorSpeed);
      Movement.moveBL(BLAuton - t_motorSpeed);
      Movement.moveBR(BRAuton - t_motorSpeed);

      // if the pid loop has reached target
      if (((error <= tolerance) && (error >= -tolerance)))
      {
        reachedGoal = true;
      }
      else
      {
        reachedGoal = false;
      }

      if (reachedGoal && t_reachedGoal)
      {
        Movement.moveLeft(0);
        Movement.moveRight(0);
        break;
      }

      delay(PIDspeed);
    }
    return 1;
  }
  bool untilColorFound(bool isBlue){
    int offset = 50;
    int redTarget = 360;
    int blueTarget = 200;
    double colorVal = Police.get_hue();
    if (isBlue)
      {
        if (colorVal <= offset || colorVal >= redTarget - offset && Police.get_proximity() > 100)
        {
          return false;
        }
      }
      else
      {
        if (colorVal >= blueTarget - offset && colorVal <= blueTarget + offset && Police.get_proximity() > 100)
        {
          return false;
        }
      }
      return true;
  }
  //update bongo current pos
  static void updatePos(void *)
  {
    delay(2000);
        while (Vincent.is_calibrating())
        {
          printf("Waitggn");
          delay(10);
        }
    /*
    TODO
    reduce movement whilst turning
    */
    double wheelCircumfrence = 8.65795;
    //offset for auton starting pos
    double head = Vincent.get_rotation() + angleOffset;
    double rightOdomVal;
    double leftOdomVal;
    //0.055
    double radius = 3.12;
    //double prev = 0;
    //double tolerance = 0.01;
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
      //head = Vincent.get_rotation();
      //double changePheta = (head - prev);
      //double correction = ((changePheta < tolerance) ? 0 : changePheta) * radius;
      //double initialVal = -rightOdom.get() - correction;
      double initialVal = -rightOdom.get();
      rightOdomVal = myMath.toInch(initialVal, wheelCircumfrence);
      //printf("h %f \n", head);
      //printf("P %f \n", prev);
      //printf("CP %f \n", changePheta);
      //printf("c %f  \n", correction);
      //printf("i %f  \n", initialVal);
      //printf("v %f \n", rightOdomVal);
      leftOdomVal = leftOdom.get();
      if (recordLocation)
      {
        // YWhee
        Y += rightOdomVal * cos(head * M_PI / 180);
        X += rightOdomVal * sin(head * M_PI / 180);

        // X wheel
        Y -= myMath.toInch(leftOdomVal * sin(head * M_PI / 180),
                           wheelCircumfrence);
        X += myMath.toInch(leftOdomVal * cos(head * M_PI / 180),
                           wheelCircumfrence);
      }

      //debug

      // reset
      //prev = head;
      rightOdom.reset();
      leftOdom.reset();
      head = Vincent.get_rotation() + angleOffset;
      c::task_delay(posDelay);
    }
  }

  void toggleEject(){
    ballToggle = !ballToggle;
    led.set_value(ballToggle? 0 : 1);
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
  }

  // checks to see if a ball has passed TODO make async
  static bool passBall()
  {
    // define precautions if ball doesnt output
    int maxTime = 5000; //time in ms before shutoff
    int maxIterations = maxTime / delayVisionTime;
    int iterations = 0;
    const int darkThreshold = 100;
    bool currentBall = false;

    while (true)
    {
      // gets current value of reflectivity of line tracker
      // high val == light enviroment
      double val = outtakeSense.get_proximity();
      //printf("value: %d \n", val);
      if (iterations >= maxIterations)
      {
        printf("end \n");
        break;
      }
      else
      {
        iterations++;
      }

      if (val >= darkThreshold)
      {
        currentBall = true;
      }
      else if (val <= darkThreshold && currentBall)
      {
        // if the ball has been logged and the value reads light again
        currentBall = false;
        printf("found \n");
        return false;
      }

      delay(delayVisionTime);
    }
  }

  //handler for the outake process
  static void waitUntilBallPasses()
  {
    printf("werhg");
    Movement.flywheel.flywheelset(true);
    //uptake has to go down to output now
    Movement.uptake.setSpeed(30);

    // max flywheel speed
    Movement.flywheel.setSpeed(100);
    //Flywheel.move_velocity(myMath.toRPM(true, 100,
    //                                    Flywheel.get_gearing()));
    Movement.customFlush();

    // wait until the ball passes the back
    passBall();

    // sets flywheel to output top
    Movement.flywheel.setSpeed(Movement.flywheel.speedMedium);

    // corrects uptake
    Movement.uptake.setSpeed(100);

    Movement.customFlushRev();
  }

  //handle outake checking
  static void handleOutake(void *)
  {
    delay(1500);
    int offset = 50;
    int redTarget = 360;
    int blueTarget = 200;
    // while false lol
    while (true)
    {
      if(ballToggle){
        // red
        if (teamIsBlue)
        {
          if (Police.get_hue() <= offset || Police.get_hue() >= redTarget - offset && Police.get_proximity() > 100)
          {
            printf("triggered");
            waitUntilBallPasses();
          }
        }
        else
        {
          if (Police.get_hue() >= blueTarget - offset && Police.get_hue() <= blueTarget + offset && Police.get_proximity() > 100)
          {
            printf("triggered");
            waitUntilBallPasses();
          }
        }
      } else {
        //printf("Disabled");
      }
      c::task_delay(15);
    }
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
    Movement.flywheel.flywheelset(true);
    Movement.flywheel.setSpeed(100);
    // deploy da boi
    Movement.intake.activate(true);
    Movement.intake.open(true);
    delay(1000);
    //inward
    Movement.intake.open(false);
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
      }
      else
      {
      }
    }
    else
    {
      // run RED SIDE second code
      if (left)
      {
      }
      else
      {
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
        
      }
    }
    else
    {
      // run RED SIDE third code
      if (left)
      {
        //init auton 
        Vincent.reset();
        delay(2000);
        while (Vincent.is_calibrating())
        {
          printf("Waitn");
          delay(10);
        }
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(50);
        Movement.uptake.setToggle(true);
        // deploy da boi
        Movement.intake.activate(true);
        Movement.intake.open(true);
        delay(400);
        Movement.intake.open(false);
        delay(400);
        setPos(96, 12);
        Movement.intake.activate(false);
        Movement.intake.holdPos(true);
        Movement.intake.keepAtPos(Movement.intake.middle);
        //go to right tower
        PIDMove(108, 36);
        PIDTurn(135);
        //line up
        //Movement.autonLineUpTower();
        //go forward with stiff arms
        Movement.moveTimed(100, 1200);
        //uptake and shoot
        delay(2000);
        //backout
        Movement.moveTimed(-100, 900);
        //go to opposite side and turn
        PIDMove(36, 36);
        PIDTurn(225);
        //line up
        //Movement.autonLineUpTower();
        Movement.autonLineUpBall();
        //go forward and uptake
        Movement.moveTimed(100, 1100);
        //uptake
        delay(2000);
        //backout and turn to path
        Movement.moveTimed(-100, 900);
        Movement.intake.activate(true);
        Movement.intake.holdPos(false);
        PIDTurn(360);
      }
      else
      {
        //init auton 
        Vincent.reset();
        delay(2500);
        while (Vincent.is_calibrating())
        {
          printf("Waitn");
          delay(10);
        }
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(50);
        //Movement.uptake.setToggle(true);
        setPos(112, 9);
        //go to right tower
        PIDMove(120, 24);
        // deploy da boi
        Movement.intake.activate(true);
        Movement.intake.open(true);
        delay(400);
        Movement.intake.open(false);
        delay(400);
        Movement.uptake.setToggle(true);
        Movement.moveTimed(100, 400);
       
        while(untilColorFound(teamIsBlue)){
          delay(10);
        }
        Movement.uptake.setToggle(false);
        PIDMove(72, 36);
        PIDTurn(180);
        Movement.uptake.setToggle(true);
        delay(1000);

        PIDMove(36, 36);
        PIDTurn(225);
        //line up
        //Movement.autonLineUpTower();
        Movement.autonLineUpBall();
        //go forward and uptake
        Movement.moveTimed(100, 1100);
        //uptake
        delay(2000);
        //backout and turn to path
        Movement.moveTimed(-100, 900);
        Movement.intake.activate(true);
        Movement.intake.holdPos(false);
        PIDTurn(360);



        /*
        old
        while (Vincent.is_calibrating())
        {
          delay(10);
        }
        Movement.flywheel.flywheelset(true);
        Movement.flywheel.setSpeed(50);
        // deploy da boi
        Movement.intake.activate(true);
        delay(400);
        Movement.intake.open(true);
        delay(400);
        //inward
        Movement.intake.open(false);
        //set pos right facing inward
        setPos(117, 10);
        //halfway inbetween 2 right towers with someadded space
        PIDMove(72, 34);
        //turn 90 relative to orgin to tower
        PIDTurn(-180);
        Movement.intake.open(true);
        //line up
        Movement.autonLineUpTower();
        //go to tower but not in
        Movement.moveTimed(100, 800);
        //cycle
        Movement.intake.open(false);
        Movement.uptake.setToggle(true);
        while(untilColorFound(!teamIsBlue)){
          delay(10);
        }
        Movement.intake.open(true);
        delay(500);
        Movement.uptake.setToggle(false);
        //go to other side of feild
        PIDMove(48, 42);
        //turn to opposite tower
        PIDTurn(-135);
        //go forward a bit then line up
        Movement.moveTimed(100, 900);
        //lockarms
        Movement.intake.activate(false);
        Movement.intake.holdPos(true);
        Movement.intake.keepAtPos(Movement.intake.middle);
        Movement.autonLineUpTower();
        //go to tower corner
        Movement.moveTimed(100, 1000);
        //shoot
        Movement.uptake.setToggle(true);
        //unlock arms
        Movement.intake.holdPos(false);
        Movement.intake.activate(true);
        Movement.intake.open(false);
        //cycle
        while(untilColorFound(!teamIsBlue)){
          delay(10);
        }
        Movement.intake.open(true);
        delay(1000);
        //get out
        Movement.uptake.setToggle(false);
        Movement.intake.activate(false);
        PIDMove(30, 30);
        Movement.moveLeft(0);
        Movement.moveRight(0);
        PIDTurn(0);
        */

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
