#include "staticFunctions.h"

class globalThreads {
private:
  thread tempThread;
  thread inertialThread;
  thread encodersThread;
  thread moveForwardPID;
public:
  void displayTemp(bool display, int delay) {
    if (display) {
      tempDisplaying = true;
      delayTempTime = delay;
      tempThread = thread(tempThreadCallback);
    } else {
      tempDisplaying = false;
      tempThread.interrupt();
    }
  }
  void displayInertial(bool display, int delay) {
    if (display) {
      inertialDisplaying = true;
      delayInertialTime = delay;
      inertialThread = thread(inertialThreadCallback);
    } else {
      inertialDisplaying = false;
      inertialThread.interrupt();
    }
  }
  void displayMotorEncoders(bool display, int delay) {
    if (display) {
      encodersDisplaying = true;
      delayEncodersTime = delay;
      encodersThread = thread(encodersThreadCallback);
    } else {
      encodersDisplaying = false;
      encodersThread.interrupt();
    }
  }
};
