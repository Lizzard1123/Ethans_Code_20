
/*

   lv_obj_t *myButton;
   lv_obj_t *myButtonLabel;
   lv_obj_t *myLabel;

   lv_style_t myButtonStyleREL; // relesed style
   lv_style_t myButtonStylePR;  // pressed style

   static lv_res_t btn_click_action(lv_obj_t *btn)
   {
   uint8_t id = lv_obj_get_free_num(btn); // id usefull when there are multiple
                                         // buttons

   if (id == 0)
   {
    char buffer[100];
    sprintf(buffer,
            "button was clicked %i milliseconds from start",
            pros::millis());
    lv_label_set_text(myLabel, buffer);
   }

   return LV_RES_OK;
   }


   lv_style_copy(&myButtonStyleREL, &lv_style_plain);
   myButtonStyleREL.body.main_color = LV_COLOR_MAKE(150, 0, 0);
   myButtonStyleREL.body.grad_color = LV_COLOR_MAKE(0, 0, 150);
   myButtonStyleREL.body.radius     = 0;
   myButtonStyleREL.text.color      = LV_COLOR_MAKE(255, 255, 255);

   lv_style_copy(&myButtonStylePR, &lv_style_plain);
   myButtonStylePR.body.main_color = LV_COLOR_MAKE(255, 0, 0);
   myButtonStylePR.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
   myButtonStylePR.body.radius     = 0;
   myButtonStylePR.text.color      = LV_COLOR_MAKE(255, 255, 255);

   myButton = lv_btn_create(lv_scr_act(), NULL);

   // create button, lv_scr_act() is deafult screen object
   lv_obj_set_free_num(myButton, 0);

   // set button is to 0
   lv_btn_set_action(myButton, LV_BTN_ACTION_CLICK, btn_click_action);

   // set function to be called on button click
   lv_btn_set_style(myButton, LV_BTN_STYLE_REL, &myButtonStyleREL);

   // set the relesed style
   lv_btn_set_style(myButton, LV_BTN_STYLE_PR,  &myButtonStylePR);

   // set the pressed style
   lv_obj_set_size(myButton, 200, 50);

   // set the button size
   lv_obj_align(myButton, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 10);

   // set the position to top mid

   myButtonLabel = lv_label_create(myButton, NULL);

   // create label and puts it inside of the button
   lv_label_set_text(myButtonLabel, "Click the Button");

   // sets label text

   myLabel = lv_label_create(lv_scr_act(), NULL);

   // create label and puts it on the screen
   lv_label_set_text(myLabel, "Button has not been clicked yet");

   // sets label text
   lv_obj_align(myLabel, NULL, LV_ALIGN_IN_LEFT_MID, 10, 0);

   // set the position to center
 */

#include "custom/autonomous.h"

//define pages


static lv_res_t btn_click_action(lv_obj_t *btn)
{
        uint8_t id = lv_obj_get_free_num(btn); // id usefull when there are multiple
        switch(lv_obj_get_free_num(btn)) {
        case 0: //red button
                Bongo.setRed();
                break;
        case 1://Blue button
                Bongo.setBlue();
                break;
        case 2://red button

                break;
        case 3://red button

                break;
        case 4: //red button

                break;
        case 5://red button

                break;
        case 6://red button

                break;
        case 7://red button

                break;
        case 8://red button

                break;
        case 9: //red button

                break;

        }
        return LV_RES_OK;
}

void initPracScreen(){

}

void initScreen(){
        //Comp!
        if(competition::is_connected ()) {

        } else { //Regular
                initPracScreen();
        }
}
