#include "custom/autonomous.h"
#include"custom/screen.h"


void initialize(){
    lv_style_t colorPageStyle;
    lv_style_copy(&colorPageStyle, &lv_style_plain);

    lv_style_t redBoxStyle;
    lv_style_copy(&redBoxStyle, &lv_style_plain);
    redBoxStyle.text.color = LV_COLOR_MAKE(0, 0, 0);
    redBoxStyle.body.main_color = LV_COLOR_MAKE(200, 0, 0);

    lv_style_t redBoxStylePR;
    lv_style_copy(&redBoxStyle, &lv_style_plain);
    redBoxStylePR.text.color = LV_COLOR_MAKE(0, 0, 0);
    redBoxStylePR.body.main_color = LV_COLOR_MAKE(150, 0, 0);

    lv_style_t blueBoxStyle;
    lv_style_copy(&blueBoxStyle, &lv_style_plain);
    blueBoxStyle.text.color = LV_COLOR_MAKE(0, 0, 0);
    blueBoxStyle.body.main_color = LV_COLOR_MAKE(0, 0, 200);

    lv_style_t blueBoxStylePR;
    lv_style_copy(&blueBoxStyle, &lv_style_plain);
    blueBoxStylePR.text.color = LV_COLOR_MAKE(0, 0, 0);
    blueBoxStylePR.body.main_color = LV_COLOR_MAKE(0, 0, 150);

    lv_obj_t * colorPage = lv_cont_create(lv_scr_act(), NULL);
    lv_cont_set_layout(colorPage, LV_LAYOUT_CENTER);
     lv_obj_set_size(colorPage, LV_HOR_RES, LV_VER_RES);
     lv_obj_align(colorPage, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

     lv_obj_t * redBox = lv_btn_create(colorPage, NULL); //create button, lv_scr_act() is deafult screen object
     lv_obj_set_free_num(redBox, 0); //set button is to 0
     lv_btn_set_action(redBox, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
     lv_btn_set_style(redBox, LV_BTN_STYLE_REL, &redBoxStyle);
     lv_btn_set_style(redBox, LV_BTN_STYLE_PR, &redBoxStylePR);
    lv_cont_set_layout(redBox, LV_LAYOUT_COL_L);
     lv_obj_set_size(redBox, LV_HOR_RES/2, LV_VER_RES);
     lv_obj_align(redBox, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);
     lv_obj_t * redBoxLabel = lv_label_create(redBox, NULL); //create label and puts it inside of the button
    lv_label_set_text(redBoxLabel, "RED");

     lv_obj_t * blueBox = lv_btn_create(colorPage, NULL); //create button, lv_scr_act() is deafult screen object
     lv_obj_set_free_num(blueBox, 1); //set button is to 0
     lv_btn_set_action(blueBox, LV_BTN_ACTION_CLICK, btn_click_action); //set function to be called on button click
     lv_btn_set_style(blueBox, LV_BTN_STYLE_REL, &blueBoxStyle);
     lv_btn_set_style(blueBox, LV_BTN_STYLE_PR, &blueBoxStylePR);
    lv_cont_set_layout(blueBox, LV_LAYOUT_COL_R);
     lv_obj_set_size(blueBox, LV_HOR_RES/2, LV_VER_RES);
     lv_obj_align(blueBox, NULL, LV_ALIGN_IN_TOP_LEFT, LV_HOR_RES/2, 0);
     lv_obj_t * blueBoxLabel = lv_label_create(blueBox, NULL); //create label and puts it inside of the button
    lv_label_set_text(blueBoxLabel, "BLUE");

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
