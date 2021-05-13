#ifndef MOVE
#define MOVE
#include "flywheel.h"
#include "intake.h"
#include "uptake.h"
#include "math.h"
class RobotMovement
{
private:
  //MY NAME IS ETHAN AND IM DUMB
  // how much the encodervaleues change the speed
  // one means for every encoder value different add to speed
  double headingScale = .5;
  double angleOffsetMove = 90;
  double LXaxis = 0;
  double LYaxis = 0;
  double RXaxis = 0;
  double RYaxis = 0;

  // experimental turn value down
  //higher the number the slower the turn
  double tune = 1.5;
  double flushspeed = 60;
  bool currenttoggleState = false;

  // takes in inputs and makes final speed
  double FLspeed;
  double FRspeed;
  double BLspeed;
  double BRspeed;

  // porpotionate algorythm
  double under;

  // speed using arrows
  double cardinalspeed = 30;

  //tower PID vars
  // neg right pos left angle
  double offset = -25;
  double error;
  double targetCX;
  double CX;
  double width;
  double error_past = 0;
  double Dval = 2;
  double Pval = .3;
  double widthLimit = 20;

  //ball PID vars
  // more goes to the right
  double ball_offset = 150;
  double ball_error;
  double ball_targetCX;
  double ball_CX;
  double ball_width;
  double ball_error_past = 0;
  double ball_Dval = 2;
  double ball_Pval = .02; // was .2
  double ball_widthLimit = 20;

  //deadzone : min num to be detected from joystick
  double deadZone = 5;

public:
  /*subsytem class declarions of the bot*/
  //flywheel obj
  flywheelClass flywheel;
  //intake obj
  intakeClass intake;
  //uptake obj
  uptakeClass uptake;
  //custom math reference
  Math myMath;

  /*
  directional arrays for cardinal directions
  FL FR BL BR
  true if negative
  */
  //motor map to move forward
  bool upDirections[4] = {false, false, false, false};
  //motor map to move right
  bool rightDirections[4] = {false, true, true, false};
  //motor map to move down
  bool downDirections[4] = {true, true, true, true};
  //motor map to move left
  bool leftDirections[4] = {true, false, false, true};

  // clears rotations for all motor encoders
  void clearRotations()
  {
    c::motor_set_zero_position(FLPort, 0);
    c::motor_set_zero_position(FRPort, 0);
    c::motor_set_zero_position(BLPort, 0);
    c::motor_set_zero_position(BRPort, 0);
  }

  //async PID for changing angle to tower green
  double lineUpTower(bool set = false)
  {
    // take signature
    vision_object_s_t tower = EYES.get_by_sig(0, EYES__CUSTOM_GREEN_NUM);
    //error = 100;
    if (tower.width >= widthLimit)
    {
      width = tower.width;
      CX = tower.x_middle_coord;
      //custom formula for dist turn
      printf("Error: %f", error);
      targetCX = -1.3286 * width + 140.619 + offset;
      error = CX - targetCX;
      FLspeed += (Pval * error + Dval * ((error - error_past) / 5)/*time delay*/);
      FRspeed -= (Pval * error + Dval * ((error - error_past) / 5)/*time delay*/);
      BLspeed += (Pval * error + Dval * ((error - error_past) / 5)/*time delay*/);
      BRspeed -= (Pval * error + Dval * ((error - error_past) / 5)/*time delay*/);
      if (set)
      {
        moveFL(Pval * error);
        moveFR(Pval * -error);
        moveBL(Pval * error);
        moveBR(Pval * -error);
      }
      error_past = error;
    }
    return error;
  }

  //async PID for lining up with ball
  double lineUpBall(bool set = false)
  {
    printf("Finding");
    vision_object_s_t BLUEBALL = Big_Brother.get_by_sig(0, Big_Brother_CUSTOMBLUE_SIG_NUM);
    vision_object_s_t REDBALL = Big_Brother.get_by_sig(0, Big_Brother_CUSTOMRED_SIG_NUM);
    if (REDBALL.width >= ball_widthLimit)
    {
      printf("Found Red Ball");
      ball_width = REDBALL.width;
      // neg right pos left
      ball_CX = REDBALL.x_middle_coord;
      //ball_targetCX = -1.3286 * ball_width + 140.619 + ball_offset;
      ball_targetCX = 158 - ball_CX + ball_offset;
      ball_error = ball_CX - ball_targetCX;
      printf("ball_error: %f \n", ball_error);
      FLspeed += (ball_Pval * ball_error + ball_Dval * ((ball_error - ball_error_past) / 5)/*time delay*/);
      FRspeed -= (ball_Pval * ball_error + ball_Dval * ((ball_error - ball_error_past) / 5)/*time delay*/);
      BLspeed += (ball_Pval * ball_error + ball_Dval * ((ball_error - ball_error_past) / 5)/*time delay*/);
      BRspeed -= (ball_Pval * ball_error + ball_Dval * ((ball_error - ball_error_past) / 5)/*time delay*/);
      if (set)
      {
        moveFL(ball_Pval * ball_error);
        moveFR(ball_Pval * -ball_error);
        moveBL(ball_Pval * ball_error);
        moveBR(ball_Pval * -ball_error);
      }
      ball_error_past = ball_error;
    }
    else if (BLUEBALL.width >= ball_widthLimit)
    {
      printf("Found Blue Ball");
      ball_width = BLUEBALL.width;
      // neg right pos left
      ball_CX = BLUEBALL.x_middle_coord;
      //ball_targetCX = -1.3286 * ball_width + 140.619 + ball_offset;
      ball_targetCX = 158 - ball_CX + ball_offset;
      ball_error = ball_CX - ball_targetCX;
      printf("ball_error: %f \n", ball_error);
      FLspeed += ball_Pval * ball_error;
      FRspeed -= ball_Pval * ball_error;
      BLspeed += ball_Pval * ball_error;
      BRspeed -= ball_Pval * ball_error;
      if (set)
      {
        moveFL(ball_Pval * ball_error);
        moveFR(ball_Pval * -ball_error);
        moveBL(ball_Pval * ball_error);
        moveBR(ball_Pval * -ball_error);
      }
    }
    return ball_error;
  }

  void autonLineUpBall()
  {
    int val = 0;
    int count = 3;
    int tolerance = 3;
    while (true)
    {
      val = lineUpBall(true);
      if (val < tolerance && val > -tolerance)
      {
        count++;
      }

      if (count > 6)
      {
        break;
      }
      delay(10);
    }
  }

  void autonLineUpTower()
  {
    int val = 0;
    int count = 3;
    int tolerance = 3;
    while (true)
    {
      val = lineUpTower(true);
      if (val < tolerance && val > -tolerance)
      {
        count++;
      }

      if (count > 6)
      {
        break;
      }
      delay(10);
    }
  }

  // moves in cardinal directions
  void cardinalMove(bool forward[])
  {
    double FLcurrent = c::motor_get_position(FLPort);
    double FRcurrent = c::motor_get_position(FRPort);
    double BLcurrent = c::motor_get_position(BLPort);
    double BRcurrent = c::motor_get_position(BRPort);
    double average = myMath.getAverage(fabs(FLcurrent), fabs(FRcurrent),
                                       fabs(BLcurrent), fabs(BRcurrent));
    double FLscale = myMath.scale(average, fabs(FLcurrent), headingScale);
    double FRscale = myMath.scale(average, fabs(FRcurrent), headingScale);
    double BLscale = myMath.scale(average, fabs(BLcurrent), headingScale);
    double BRscale = myMath.scale(average, fabs(BRcurrent), headingScale);

    FLspeed =
        forward[0] ? -(cardinalspeed + FLscale) : (cardinalspeed + FLscale);
    FRspeed =
        forward[1] ? -(cardinalspeed + FRscale) : (cardinalspeed + FRscale);
    BLspeed =
        forward[2] ? -(cardinalspeed + BLscale) : (cardinalspeed + BLscale);
    BRspeed =
        forward[3] ? -(cardinalspeed + BRscale) : (cardinalspeed + BRscale);
  }

  // upadate controller vars for bongo orientation
  void catieControll()
  {
    LXaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_X));
    LYaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    RXaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) / tune;
    RYaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y));

    FLspeed = RYaxis + RXaxis;
    FRspeed = RYaxis - RXaxis;
    BLspeed = RYaxis + RXaxis;
    BRspeed = RYaxis - RXaxis;

    // set speeds in order to move bongo in target agle taken into account
    // current angle
    if (((LXaxis > deadZone) || (LXaxis < -deadZone)) ||
        ((LYaxis > deadZone) || (LYaxis < -deadZone)))
    {
      // updates speed
      double speed = myMath.TwoPointsDistance(0, 0, LXaxis, LYaxis);

      // find the angle between straight forward
      double Dangle = acos(LYaxis / speed) * 180 / M_PI;

      // negative if the x axis is on left or neg
      if (LXaxis < 0)
      {
        Dangle *= -1;
      }

      // current angle
      double currentAngle = Vincent.get_rotation() + angleOffsetMove;
      FLspeed += myMath.sRound(
          myMath.multiplier(FLnum, currentAngle, Dangle) * speed, 3);
      FRspeed += myMath.sRound(
          myMath.multiplier(FRnum, currentAngle, Dangle) * speed, 3);
      BLspeed += myMath.sRound(
          myMath.multiplier(BLnum, currentAngle, Dangle) * speed, 3);
      BRspeed += myMath.sRound(
          myMath.multiplier(BRnum, currentAngle, Dangle) * speed, 3);
    }

    //under is the number in the denominator of the largest number when it equals 100
    //scales down other numbers relative to it
    double under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                                   fabs(BRspeed)) /
                   100;
    FLspeed = (FLspeed / under);
    FRspeed = (FRspeed / under);
    BLspeed = (BLspeed / under);
    BRspeed = (BRspeed / under);
  }

  // upadate controller vars for bongo orientation
  //AKA tyler drive
  void updateControllerAxis()
  {
    LXaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_X));
    LYaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    RXaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) / tune;
    FLspeed = LYaxis + LXaxis + RXaxis;
    FRspeed = LYaxis - LXaxis - RXaxis;
    BLspeed = LYaxis - LXaxis + RXaxis;
    BRspeed = LYaxis + LXaxis - RXaxis;

    //under is the number in the denominator of the largest number when it equals 100
    //scales down other numbers relative to it
    double under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                                   fabs(BRspeed)) /
                   100;

    FLspeed = (FLspeed / under);
    FRspeed = (FRspeed / under);
    BLspeed = (BLspeed / under);
    BRspeed = (BRspeed / under);
  }

  // drives motors from private vars AKA refresh motor speeds
  void move()
  {
    FR.move_velocity(myMath.toRPM(false, FRspeed, FR.get_gearing()));
    FL.move_velocity(myMath.toRPM(false, FLspeed, FL.get_gearing()));
    BR.move_velocity(myMath.toRPM(false, BRspeed, BR.get_gearing()));
    BL.move_velocity(myMath.toRPM(false, BLspeed, BL.get_gearing()));
  }

  //update left motor side of bongo
  void moveTimed(double speed, double time)
  {
    FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing()));
    BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing()));
    FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing()));
    BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing()));
    delay(time);
    FL.move_velocity(0);
    BL.move_velocity(0);
    FR.move_velocity(0);
    BR.move_velocity(0);
  }

  //update left motor side of bongo
  void moveLeft(double speed)
  {
    FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing()));
    BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing()));
  }

  //update right motor side of bongo
  void moveRight(double speed)
  {
    FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing()));
    BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing()));
  }

  //individually set FL motor speed;
  void moveFL(double speed)
  {
    FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing()));
  }

  //individually set FR motor speed;
  void moveFR(double speed)
  {
    FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing()));
  }

  //individually set BL motor speed;
  void moveBL(double speed)
  {
    BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing()));
  }

  //individually set BR motor speed;
  void moveBR(double speed)
  {
    BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing()));
  }

  // sets intake and uptake to flush if true
  void flush(bool setting)
  {
    intake.open(setting);
    uptake.flush(setting);
  }

  //experimental kinda flush uptake and output w/ flywheel
  void customFlush()
  {
    printf("Insidf");
    uptake.flush(true);
    flywheel.outputBall(true);
  }

  //sets uptake flush to false and flywheel output to false
  void customFlushRev()
  {
    printf("Insidg");
    uptake.flush(false);
    flywheel.outputBall(false);
  }

  // stops all movement
  void stopAll()
  {
    intake.activate(false);
    uptake.setToggle(false);
    flywheel.flywheelset(false);
    moveLeft(0);
    moveRight(0);
  }
};
#endif // ifndef MOVE
