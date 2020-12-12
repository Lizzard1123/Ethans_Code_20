#include "custom/autonomous.h"
#include"custom/screen.h"


void initialize(){
    lv_init();

    static lv_style_t redBoxStyle;
    lv_style_copy(&redBoxStyle, &lv_style_plain);
    redBoxStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
    redBoxStyle.body.border.width = 5;
    redBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
    redBoxStyle.body.main_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
    redBoxStyle.body.grad_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);

    static lv_style_t redBoxStylePR;
    lv_style_copy(&redBoxStylePR, &lv_style_plain);
    redBoxStylePR.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
    redBoxStyle.body.border.width = 5;
    redBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
    redBoxStylePR.body.main_color = LV_COLOR_MAKE(0x96, 0x00, 0x00);
    redBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x96, 0x00, 0x00);

    static lv_style_t blueBoxStyle;
    lv_style_copy(&blueBoxStyle, &lv_style_plain);
    blueBoxStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
    blueBoxStyle.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
    blueBoxStyle.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);

    static lv_style_t blueBoxStylePR;
    lv_style_copy(&blueBoxStylePR, &lv_style_plain);
    blueBoxStylePR.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
    blueBoxStylePR.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0x96);
    blueBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0x96);

    lv_obj_t * scrColor = lv_obj_create(NULL, NULL);

     lv_obj_t * redBox = lv_btn_create(scrColor, NULL); //create button, lv_scr_act() is deafult screen object

     lv_btn_set_action(redBox, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
     setupButton(redBox, 0, redBoxStyle, redBoxStylePR, LV_HOR_RES/2, LV_VER_RES, 5, 0, 0);

     lv_obj_t * redBoxLabel = lv_label_create(redBox, NULL); //create label and puts it inside of the button
    lv_label_set_text(redBoxLabel, "RED");

     lv_obj_t * blueBox = lv_btn_create(scrColor, NULL); //create button, lv_scr_act() is deafult screen object
     lv_obj_set_free_num(blueBox, 1); //set button is to 0
     lv_btn_set_action(blueBox, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
     lv_btn_set_style(blueBox, LV_BTN_STYLE_REL, &blueBoxStyle);
     lv_btn_set_style(blueBox, LV_BTN_STYLE_PR, &blueBoxStylePR);
    lv_cont_set_layout(blueBox, LV_LAYOUT_COL_R);
     lv_obj_set_size(blueBox, LV_HOR_RES/2, LV_VER_RES);
     lv_obj_set_pos(blueBox, LV_HOR_RES/2, 0);
     lv_obj_t * blueBoxLabel = lv_label_create(blueBox, NULL); //create label and puts it inside of the button
    lv_label_set_text(blueBoxLabel, "BLUE");


lv_scr_load(scrColor);


  FL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  FR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  BL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  BR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  Flywheel.set_brake_mode(E_MOTOR_BRAKE_COAST);
  Lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  RArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

  delay(250);
  Bongo.init();
}

void disabled()               {}

void competition_initialize() {}
