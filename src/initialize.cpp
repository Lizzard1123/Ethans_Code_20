#include "custom/autonomous.h"
#include "custom/screen.h"


lv_obj_t *scrColor = lv_obj_create(NULL, NULL);

lv_obj_t *redBox = lv_btn_create(scrColor, NULL);

lv_obj_t *redBoxLabel = lv_label_create(redBox, NULL);   // create label and
                                                         // puts it inside of
                                                         // the button


lv_obj_t *blueBox = lv_btn_create(scrColor, NULL);       // create button,
                                                         // lv_scr_act() is
                                                         // deafult screen
                                                         // object


lv_obj_t *blueBoxLabel = lv_label_create(blueBox, NULL); // create label and
                                                         // puts it inside of
                                                         // the button

static lv_res_t btn_click_action(lv_obj_t *btn)
{
  uint8_t id = lv_obj_get_free_num(btn); // id usefull when there are multiple

  switch (lv_obj_get_free_num(btn)) {
  case 0:                                // red button
    Bongo.setRed();
    lv_label_set_text(redBoxLabel,  "    RED\n(SELECTED)");
    lv_label_set_text(blueBoxLabel, "BLUE");
    break;

  case 1: // Blue button
    Bongo.setBlue();
    lv_label_set_text(blueBoxLabel, "    BLUE \n(SELECTED)");
    lv_label_set_text(redBoxLabel,  "RED");
    break;

  case 2: // red button

    break;

  case 3: // red button

    break;

  case 4: // red button

    break;

  case 5: // red button

    break;

  case 6: // red button

    break;

  case 7: // red button

    break;

  case 8: // red button

    break;

  case 9: // red button

    break;
  }
  return LV_RES_OK;
}

void setupButton(lv_obj_t *obj,
                 int       num,
                 double    width,
                 double    height,
                 double    borderSize,
                 double    x,
                 double    y) {
  lv_obj_set_free_num(obj, num);
  lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_obj_set_size(obj, width, height);
  lv_obj_set_pos(obj, x + borderSize, y + borderSize);
}

void initPrac() {
  static lv_style_t buttonBoxStyle;


  static lv_style_t redBoxStyle;


  static lv_style_t redBoxStylePR;


  static lv_style_t blueBoxStyle;


  static lv_style_t blueBoxStylePR;

  lv_style_copy(&buttonBoxStyle, &lv_style_plain);
  buttonBoxStyle.text.color        = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  buttonBoxStyle.body.border.width = 5;
  buttonBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  lv_style_copy(&redBoxStyle,    &buttonBoxStyle);
  redBoxStyle.body.main_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
  redBoxStyle.body.grad_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
  lv_style_copy(&redBoxStylePR,  &buttonBoxStyle);
  redBoxStylePR.body.main_color = LV_COLOR_MAKE(0x96, 0x00, 0x00);
  redBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x96, 0x00, 0x00);
  lv_style_copy(&blueBoxStyle,   &buttonBoxStyle);
  blueBoxStyle.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
  blueBoxStyle.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8); \
  lv_style_copy(&blueBoxStylePR, &buttonBoxStyle);
  blueBoxStylePR.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0x96);
  blueBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0x96);

  setupButton(redBox, 0, LV_HOR_RES / 2, LV_VER_RES, 5, 0, 0);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(redBox, LV_BTN_STYLE_REL, &redBoxStyle);
  lv_btn_set_style(redBox, LV_BTN_STYLE_PR,  &redBoxStylePR);

  lv_label_set_text(redBoxLabel, "RED");

  setupButton(blueBox, 1, LV_HOR_RES / 2, LV_VER_RES, 5, LV_HOR_RES / 2, 0);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(blueBox, LV_BTN_STYLE_REL, &blueBoxStyle);
  lv_btn_set_style(blueBox, LV_BTN_STYLE_PR,  &blueBoxStylePR);

  lv_label_set_text(blueBoxLabel, "BLUE");
}

void initialize() {
  lv_init();
  initPrac();

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
