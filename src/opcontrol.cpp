#include "custom/autonomous.h"



void opcontrol() {
  if (!Bongo.isinit()) {
    Bongo.initThreads();
  }
  
  // turn on flywheel
  Bongo.Movement.flywheel.flywheelset(true);

  while (true) {
    Bongo.debugPos();
    // change teams
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)) {
      Bongo.changeTeam();
      //Bongo.Autonomous();
      // gotta test arm first 
      //check the direction it is going in with the values less than 0 for direction in loop
      //if have no idea then printf value of pot to see whats up
      //if(pot.val == 8){
      // die  
      //}
      Bongo.Movement.intake.holdPos(true);
      Bongo.Movement.intake.keepAtPos(Bongo.Movement.intake.middle);
    }

    // toggle flywheel why do i need this delete?
    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
      Bongo.Movement.flywheel.flywheeltoggleswitch();
    }

    // updates controler values (tyler drive)
    Bongo.Movement.updateControllerAxis();

    // catie control
    // Bongo.Movement.catieControll();

    // cardinal Directions
    if (master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
      Bongo.Movement.cardinalMove(Bongo.Movement.upDirections);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
      Bongo.Movement.cardinalMove(Bongo.Movement.downDirections);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
      Bongo.Movement.cardinalMove(Bongo.Movement.leftDirections);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
      Bongo.Movement.cardinalMove(Bongo.Movement.rightDirections);
    } else {
      Bongo.Movement.clearRotations();
    }


    // intake control
    if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
       Bongo.Movement.intake.activate(true);
    } else {
       Bongo.Movement.intake.activate(false);
    }

    // uptake control
    if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
       Bongo.Movement.uptake.toggle();
    }

    // flush?
    if(master.get_digital(E_CONTROLLER_DIGITAL_L2)){
       Bongo.Movement.intake.open(true);
    } else {
       Bongo.Movement.intake.open(false);
    }

    // Flywheel control speed
    if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      Bongo.Movement.flywheel.setSpeed(Bongo.Movement.flywheel.speedHigh);
    } else if (master.get_digital(E_CONTROLLER_DIGITAL_Y)) {
      Bongo.Movement.flywheel.setSpeed(Bongo.Movement.flywheel.speedLow);
    } else {
      Bongo.Movement.flywheel.setSpeed(Bongo.Movement.flywheel.speedMedium);
    }

    //line up with the tower
    if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
      Bongo.Movement.lineUpTower();
    }

    //Line up with the ball
    if(master.get_digital(E_CONTROLLER_DIGITAL_Y)){
      Bongo.Movement.lineUpBall();
    }

    // starts the spin on motors or cuts power
    Bongo.Movement.move();

    delay(20);
  }
}
