#ifndef MOVE
#define MOVE
#include "flywheel.h"
#include "intake.h"
#include "uptake.h"
#include "math.h"
class RobotMovement
{
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
  void clearRotations()
  {
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
  double widthLimit = 20;

  void lineUp()
  {
    vision_object_s_t tower = EYES.get_by_sig(0, EYES__CUSTOM_GREEN_NUM);
    if (tower.width >= widthLimit)
    {
      width = tower.width;
      // neg right pos left
      CX = tower.x_middle_coord;
      targetCX = -1.3286 * width + 140.619 + offset;
      error = CX - targetCX;
      FLspeed += Pval * error;
      FRspeed -= Pval * error;
      BLspeed += Pval * error;
      BRspeed -= Pval * error;
    }
  }

  // helper func that returns number of encoder pos away from average scaled
  // from global var
  double scale(double av, double part)
  {
    return (av - part) * headingScale;
  }

  double deadZone = 5;

  // moves in cardinal directions
  void cardinalMove(bool forward[])
  {
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

    // delay(10);
  }

  // upadate controller vars for bongo orientation
  void catieControll()
  {
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
    if (((LXaxis > deadZone) || (LXaxis < -deadZone)) ||
        ((LYaxis > deadZone) || (LYaxis < -deadZone)))
    {
      // updates
      double speed = myMath.TwoPointsDistance(0, 0, LXaxis, LYaxis);

      // offset so it drives at 100% going forward
      // =speed *= 1.5;

      // find the angle between straight forward
      double Dangle = acos(LYaxis / speed) * 180 / M_PI;

      // negative if the x axis is on left or neg
      if (LXaxis < 0)
      {
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
  void updateControllerAxis()
  {
    LXaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_X));
    LYaxis = (master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y));
    RXaxis = (master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X)) / tune; // updates
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
  void moveRelative()
  {
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
    if (LXaxis < 0)
    {
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
  void alterSpeed(double speed)
  {
    under = myMath.greatest(fabs(FLspeed), fabs(FRspeed), fabs(BLspeed),
                            fabs(BRspeed)) /
            100;
    FLspeed = (FLspeed / under) * speed;
    FRspeed = (FRspeed / under) * speed;
    BLspeed = (BLspeed / under) * speed;
    BRspeed = (BRspeed / under) * speed;
  }

  // drives motors from private vars
  void move()
  {
    FR.move_velocity(myMath.toRPM(false, FRspeed, FR.get_gearing()));

    // printf("FL %f\n", FLspeed);
    FL.move_velocity(myMath.toRPM(false, FLspeed, FL.get_gearing()));

    // printf("FR %f\n", FRspeed);
    BR.move_velocity(myMath.toRPM(false, BRspeed, BR.get_gearing()));

    // printf("BL %f\n", BLspeed);
    BL.move_velocity(myMath.toRPM(false, BLspeed, BL.get_gearing()));
  }

  void moveLeft(double speed)
  {
    FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing()));
    BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing()));
  }

  void moveRight(double speed)
  {
    FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing()));
    BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing()));
  }

  void moveFL(double speed)
  {
    FL.move_velocity(myMath.toRPM(false, speed, FL.get_gearing()));
  }

  void moveFR(double speed)
  {
    FR.move_velocity(myMath.toRPM(false, speed, FR.get_gearing()));
  }

  void moveBL(double speed)
  {
    BL.move_velocity(myMath.toRPM(false, speed, BL.get_gearing()));
  }

  void moveBR(double speed)
  {
    BR.move_velocity(myMath.toRPM(false, speed, BR.get_gearing()));
  }

  // reverses motors to get a ball out front
  void flush(bool setting)
  {
    intake.flush(setting);
    uptake.flush(setting);
  }

  void customFlush(){
    uptake.flush(true);
    flywheel.outputBall(true);
  }
  void customFlushRev(){
    uptake.flush(false);
    flywheel.outputBall(false);
  }

  // stops all functions
  void stopAll()
  {
    intake.stopBoth();
    uptake.setToggle(false);
    flywheel.flywheelset(false);
  }
};
#endif // ifndef MOVE
