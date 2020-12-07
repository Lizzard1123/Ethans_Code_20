#include "basicMovement.h"
// draws to screen
void drawFire(int x, int y, int l, int w, int tx, int ty, int percent) {
  if (percent < 30) {
    Brain.Screen.setFillColor(blue);
  } else if (percent < 60) {
    Brain.Screen.setFillColor(yellow);
  } else if (percent < 80) {
    Brain.Screen.setFillColor(orange);
  } else {
    Brain.Screen.setFillColor(red);
  }
  Brain.Screen.drawRectangle(x, y, l, w);
  Brain.Screen.setPenWidth(5);
  Brain.Screen.setPenColor(black);
  Brain.Screen.printAt(tx, ty, "temp: %d%% ", percent);
}
// gives params to display func
void displayTemp() {
  Controller1.Screen.clearScreen();
  Brain.Screen.clearScreen();
  drawFire(0, 0, 240, 120, 120, 60, FL.temperature());
  drawFire(240, 0, 240, 120, 360, 60, FR.temperature());
  drawFire(0, 120, 240, 120, 120, 180, BL.temperature());
  drawFire(240, 120, 240, 120, 360, 180, BR.temperature());
  Controller1.Screen.print("Displaying Temp!");
}
// currently displaying temp on cortex
bool tempDisplaying = false;
// sleep interval for thread
int delayTempTime = 1000;

// thread Callback that displalys temp
int tempThreadCallback() {
  while (true) {
    displayTemp();
    this_thread::sleep_for(delayTempTime);
  }
  return 0;
}

// shows all interial data on cortex
void InertialTest() {
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  // Prints the pitch ( rotation around the side to side axis)
  Brain.Screen.print("Pitch Orientation (deg): ");
  Brain.Screen.print((Vincent.orientation(pitch, degrees)));
  Brain.Screen.newLine();
  // Prints the acceleration of the y axis.
  Brain.Screen.print("Y-axis Acceleration (G): ");
  Brain.Screen.print(Vincent.acceleration(yaxis));
  Brain.Screen.newLine();
  // Prints the gyro rate of the y axis
  Brain.Screen.print("Y-axis Gyro Rate (DPS): ");
  Brain.Screen.print(Vincent.gyroRate(yaxis, dps));
  Brain.Screen.newLine();
  // Print the current heading in degrees
  Brain.Screen.print("Inertial Sensor's current heading (deg): ");
  Brain.Screen.print(Vincent.heading());
  Brain.Screen.newLine();
  // Print the current angle of rotation in degrees
  Brain.Screen.print("Inertial Sensor's current angle of rotation (deg): ");
  Brain.Screen.print(Vincent.rotation());
}

// currently displaying interial on cortex
bool inertialDisplaying = false;
// sleep interval for thread
int delayInertialTime = 1000;

// thread Callback that displalys temp
int inertialThreadCallback() {
  while (true) {
    InertialTest();
    this_thread::sleep_for(delayInertialTime);
  }
  return 0;
}
// helper func for displaying motor encoders
void rotationCheckScreen(int tx, int ty, int numberof) {
  Brain.Screen.setPenWidth(10);
  Brain.Screen.setPenColor(white);
  Brain.Screen.printAt(tx - 60, ty, "rotations: %d%% ", numberof);
}
// displays motor encoders on cortex
void rotationCheck() {
  Brain.Screen.clearScreen();
  rotationCheckScreen(120, 60, FL.rotation(degrees));
  rotationCheckScreen(360, 60, FR.rotation(degrees));
  rotationCheckScreen(120, 180, BL.rotation(degrees));
  rotationCheckScreen(360, 180, BR.rotation(degrees));
}
// currently displaying motor encoders on cortex
bool encodersDisplaying = false;
// sleep interval for thread
int delayEncodersTime = 1000;

// thread Callback that displalys temp
int encodersThreadCallback() {
  while (true) {
    rotationCheck();
    this_thread::sleep_for(delayEncodersTime);
  }
  return 0;
}

// Vision Sort

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
