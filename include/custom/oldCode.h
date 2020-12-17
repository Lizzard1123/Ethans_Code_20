//backup for old / outdated / unused code
//if 0 means dont compile inside 
#if 0
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
      // Brain.Screen.setFillColor(transparent);
      // Brain.Screen.setPenColor(white);
      // Brain.Screen.setCursor(1, 1);
      // Brain.Screen.print(error);
      // Brain.Screen.setCursor(2, 1);
      // Brain.Screen.print(derivative);
      // Brain.Screen.setCursor(3, 1);
      // Brain.Screen.print(speed);
      // Brain.Screen.setCursor(4, 1);
      // Brain.Screen.print(currentAngle);
      // Brain.Screen.setCursor(5, 1);
      // Brain.Screen.print(Dangle);
      // Brain.Screen.setCursor(6, 1);
      // Brain.Screen.print(reachedGoal);



      // Brain.Screen.clearScreen();
      // Brain.Screen.setCursor(1, 1);
      // Brain.Screen.print(Vincent.rotation(degrees));
      // Brain.Screen.setCursor(2, 1);
      // Brain.Screen.print(error);
      // Brain.Screen.setCursor(3, 1);
      // Brain.Screen.print(integralone);
      // Brain.Screen.setCursor(4, 1);
      // Brain.Screen.print(Derivative);
      // Brain.Screen.setCursor(5, 1);
      // Brain.Screen.print(reachedGoal);
      // Brain.Screen.setCursor(6, 1);
      // Brain.Screen.print(motorSpeed);

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
     fabs(target)); bool reachedGoal; double LSideSpeed = 0; double RSideSpeed =
        0;
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

/*
  void setTeamColor() {
    // Brain.Screen.setCursor(1, 1);
    // Brain.Screen.print(TeamColor.value(vex::rotationUnits::deg));
    // Brain.Screen.setCursor(2, 1);
    // Brain.Screen.print(AutonNumber.value(vex::rotationUnits::deg));
    if (TeamColor.get_value() <= teamColorLow) {
      // less than angle set color blue
      // setTeamNum(true);
      teamIsBlue = true;
      left       = true;
    } else if (TeamColor.get_value() <= teamColorMiddle) {
      // less than angle set color blue
      // setTeamNum(true);
      teamIsBlue = true;
      left       = false;
    } else if (TeamColor.get_value() <= teamColorHigh) {
      // greater than angle set color red
      // setTeamNum(false);
      teamIsBlue = false;
      left       = true;
    } else {
      // greater than angle set color red
      // setTeamNum(false);
      teamIsBlue = false;
      left       = false;
    }
  }
*/

/*
  void setAuton() {
    // setup for 3 autons
    if (AutonNumber.get_value() >= autonLimitOne) {
      // set auton number 1
      // setAutoNum(1);
      autonCodeNum = 1;
    } else if (AutonNumber.get_value() >= autonLimitTwo) {
      // set auton number 2
      // setAutoNum(2);
      autonCodeNum = 2;
    } else {
      // greater than autonLimitTwo set 3rd code
      // setAutoNum(3);
      autonCodeNum = 3;
    }
  }
*/
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
    

   */


  


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