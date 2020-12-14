

#include "custom/autonomous.h"




void initPracScreen(){

}

void initScreen(){
        //Comp!
        if(competition::is_connected ()) {

        } else { //Regular
                initPracScreen();
        }
}
