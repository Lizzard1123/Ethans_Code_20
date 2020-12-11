#ifndef MATH
#define MATH
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
#endif
