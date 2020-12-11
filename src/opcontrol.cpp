#include "custom/autonomous.h"

void opcontrol() {
    if(!Bongo.isinit()){
        Bongo.init();
    }
	//turn on flywheel
  Bongo.Movement.flywheel.flywheelset(true);

	while (true) {
		//change teams
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_A)){
			Bongo.changeTeam();
		}
		//toggle flywheel
		if(master.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
			Bongo.Movement.flywheel.flywheeltoggleswitch();
		}

		//updates controler values
    	//bongo orientation
    	Bongo.Movement.updateControllerAxis();
    	//catie control
    	//Bongo.Movement.catieControll();

		// cardinal Directions
    	if (master.get_digital(E_CONTROLLER_DIGITAL_UP)) {
      		Bongo.Movement.cardinalMove(Bongo.Movement.upDirections);
    	} else if (master.get_digital(E_CONTROLLER_DIGITAL_DOWN)) {
      		Bongo.Movement.cardinalMove(Bongo.Movement.downDirections);
    	} else if (master.get_digital(E_CONTROLLER_DIGITAL_LEFT)) {
      		Bongo.Movement.cardinalMove(Bongo.Movement.leftDirections);
		}else if (master.get_digital(E_CONTROLLER_DIGITAL_RIGHT)) {
      		Bongo.Movement.cardinalMove(Bongo.Movement.rightDirections);
    	} else {
      		Bongo.Movement.clearRotations();
    	}

		if (master.get_digital(E_CONTROLLER_DIGITAL_R1) && master.get_digital(E_CONTROLLER_DIGITAL_L1)) { //intake
	      Bongo.Movement.uptake.setToggle(true);
	      Bongo.Movement.intake.activate(true);
          //printf("both");
	  	} else if(master.get_digital(E_CONTROLLER_DIGITAL_L1)){
	      Bongo.Movement.intake.activate(true);
	      Bongo.Movement.uptake.setToggle(false);
          //printf("inta");
	  	} else if(master.get_digital(E_CONTROLLER_DIGITAL_R1)){
	      Bongo.Movement.uptake.setToggle(true);
	      Bongo.Movement.intake.activate(false);
          //printf("uptake");
	  	} else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) { // flush
	      Bongo.Movement.flush(true);
          //printf("flush");
	    } else { // nothing
	      Bongo.Movement.flush(false);
	      Bongo.Movement.uptake.setToggle(false);
	      Bongo.Movement.intake.activate(false);
          //printf("none");
	    }

		if(master.get_digital(E_CONTROLLER_DIGITAL_R2)){
	      Bongo.Movement.flywheel.setSpeed(Bongo.Movement.flywheel.speedHigh);
	  	} else if (master.get_digital(E_CONTROLLER_DIGITAL_Y)){
	      Bongo.Movement.flywheel.setSpeed(Bongo.Movement.flywheel.speedLow);
	    } else {
	      Bongo.Movement.flywheel.setSpeed(Bongo.Movement.flywheel.speedMedium);
	    }

	    //if(master.get_digital(E_CONTROLLER_DIGITAL_X)){
	      //Bongo.Movement.lineUp();
	    //}
		// starts the spin on motors or cuts power
    	Bongo.Movement.move();

		delay(20);
	}
}
