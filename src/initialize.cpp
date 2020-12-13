#include "custom/autonomous.h"
#include "custom/screen.h"

lv_obj_t *scrColor = lv_obj_create(NULL, NULL);

lv_obj_t *redBox = lv_btn_create(scrColor, NULL);

lv_obj_t *redBoxLabel = lv_label_create(redBox, NULL); 

lv_obj_t *blueBox = lv_btn_create(scrColor, NULL); 

lv_obj_t *blueBoxLabel = lv_label_create(blueBox, NULL); 




lv_obj_t *scrSide = lv_obj_create(NULL, NULL);

lv_obj_t *leftBox = lv_btn_create(scrSide, NULL);

lv_obj_t *leftBoxLabel = lv_label_create(leftBox, NULL); 

lv_obj_t *rightBox = lv_btn_create(scrSide, NULL); 

lv_obj_t *rightBoxLabel = lv_label_create(rightBox, NULL); 

lv_obj_t *backBox = lv_btn_create(scrSide, NULL); 

lv_obj_t *backBoxLabel = lv_label_create(backBox, NULL); 


lv_obj_t *scrAuton = lv_obj_create(NULL, NULL);

lv_obj_t *smallBox = lv_btn_create(scrAuton, NULL);

lv_obj_t *smallBoxLabel = lv_label_create(smallBox, NULL); 

lv_obj_t *medBox = lv_btn_create(scrAuton, NULL); 

lv_obj_t *medBoxLabel = lv_label_create(medBox, NULL); 

lv_obj_t *bigBox = lv_btn_create(scrAuton, NULL); 

lv_obj_t *bigBoxLabel = lv_label_create(bigBox, NULL); 

lv_obj_t *backBox2 = lv_btn_create(scrAuton, NULL); 

lv_obj_t *backBoxLabel2 = lv_label_create(backBox2, NULL); 
                                                         
int current = 0;
void loadScreen(){
  switch(current){
    case 0:
      lv_scr_load(scrColor);
      break;
    case 1:
      lv_scr_load(scrSide);
      break;  
    case 2:
      lv_scr_load(scrAuton);
      break;  
  }
}


static lv_res_t btn_click_action(lv_obj_t *btn)
{
  uint8_t id = lv_obj_get_free_num(btn); // id usefull when there are multiple
  int interval = 100;
  switch (lv_obj_get_free_num(btn))
  {
  case 0: // red button
    Bongo.setRed();
    lv_label_set_text(redBoxLabel, "    RED\n(SELECTED)");
    lv_label_set_text(blueBoxLabel, "BLUE");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 1: // Blue button
    Bongo.setBlue();
    lv_label_set_text(blueBoxLabel, "    BLUE \n(SELECTED)");
    lv_label_set_text(redBoxLabel, "RED");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 2: // left button
    lv_label_set_text(leftBoxLabel, "    LEFT \n(SELECTED)");
    lv_label_set_text(rightBoxLabel, "RIGHT");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 3: // right button
    lv_label_set_text(rightBoxLabel, "    RIGHT \n(SELECTED)");
    lv_label_set_text(leftBoxLabel, "LEFT");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 4: // back button side
    current--;
    loadScreen();
    break;

  case 5: // small button
    lv_label_set_text(smallBoxLabel, "   SMALL \n(SELECTED)");
    lv_label_set_text(medBoxLabel, "MED");
    lv_label_set_text(bigBoxLabel, "BIG");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 6: // med button
  lv_label_set_text(medBoxLabel, "    MED \n(SELECTED)");
    lv_label_set_text(smallBoxLabel, "SMALL");
    lv_label_set_text(bigBoxLabel, "BIG");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 7: // big button
  lv_label_set_text(bigBoxLabel, "     BIG \n(SELECTED)");
    lv_label_set_text(medBoxLabel, "MED");
    lv_label_set_text(smallBoxLabel, "SMALL");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 8: // back button auton
    current--;
    loadScreen();
    break;

  case 9: // red button

    break;
  }
  return LV_RES_OK;
}

void setupButton(lv_obj_t *obj,
                 int num,
                 double width,
                 double height,
                 double borderSize,
                 double x,
                 double y)
{
  lv_obj_set_free_num(obj, num);
  lv_btn_set_action(obj, LV_BTN_ACTION_CLICK, btn_click_action);
  lv_obj_set_size(obj, width, height);
  lv_obj_set_pos(obj, x, y);
}

void initPrac()
{
  static lv_style_t buttonBoxStyle;
  lv_style_copy(&buttonBoxStyle, &lv_style_plain);
  buttonBoxStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  buttonBoxStyle.body.border.width = 5;
  buttonBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  static lv_style_t redBoxStyle;
  lv_style_copy(&redBoxStyle, &buttonBoxStyle);
  redBoxStyle.body.main_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
  redBoxStyle.body.grad_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
  static lv_style_t redBoxStylePR;
  lv_style_copy(&redBoxStylePR, &buttonBoxStyle);
  redBoxStylePR.body.main_color = LV_COLOR_MAKE(0x96, 0x00, 0x00);
  redBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x96, 0x00, 0x00);
  static lv_style_t blueBoxStyle;
  lv_style_copy(&blueBoxStyle, &buttonBoxStyle);
  blueBoxStyle.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
  blueBoxStyle.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
  static lv_style_t blueBoxStylePR;
  lv_style_copy(&blueBoxStylePR, &buttonBoxStyle);
  blueBoxStylePR.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0x96);
  blueBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0x96);

  setupButton(redBox, 0, LV_HOR_RES / 2, LV_VER_RES, 5, 0, 0);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(redBox, LV_BTN_STYLE_REL, &redBoxStyle);
  lv_btn_set_style(redBox, LV_BTN_STYLE_PR, &redBoxStylePR);

  lv_label_set_text(redBoxLabel, "RED");

  setupButton(blueBox, 1, LV_HOR_RES / 2, LV_VER_RES, 5, LV_HOR_RES / 2, 0);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(blueBox, LV_BTN_STYLE_REL, &blueBoxStyle);
  lv_btn_set_style(blueBox, LV_BTN_STYLE_PR, &blueBoxStylePR);

  lv_label_set_text(blueBoxLabel, "BLUE");
}

void initSide()
{
  static lv_style_t sideBoxStyle;
  lv_style_copy(&sideBoxStyle, &lv_style_plain);
  sideBoxStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  sideBoxStyle.body.border.width = 5;
  sideBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  static lv_style_t leftBoxStyle;
  lv_style_copy(&leftBoxStyle, &sideBoxStyle);
  leftBoxStyle.body.main_color = LV_COLOR_MAKE(0x00, 0x96, 0x0f);
  leftBoxStyle.body.grad_color = LV_COLOR_MAKE(0x00, 0x96, 0x0f);
  static lv_style_t leftBoxStylePR;
  lv_style_copy(&leftBoxStylePR, &sideBoxStyle);
  leftBoxStylePR.body.main_color = LV_COLOR_MAKE(0x00, 0x61, 0x0a);
  leftBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x96, 0x61, 0x0a);
  static lv_style_t rightBoxStyle;
  lv_style_copy(&rightBoxStyle, &sideBoxStyle);
  rightBoxStyle.body.main_color = LV_COLOR_MAKE(0xe0, 0x52, 0xc8);
  rightBoxStyle.body.grad_color = LV_COLOR_MAKE(0xe0, 0x52, 0xc8);
  static lv_style_t rightBoxStylePR;
  lv_style_copy(&rightBoxStylePR, &sideBoxStyle);
  rightBoxStylePR.body.main_color = LV_COLOR_MAKE(0xad, 0x40, 0x96);
  rightBoxStylePR.body.grad_color = LV_COLOR_MAKE(0xad, 0x40, 0x96);

  static lv_style_t backBoxStyle;
  lv_style_copy(&backBoxStyle, &sideBoxStyle);
  backBoxStyle.body.main_color = LV_COLOR_MAKE(0x9c, 0x9c, 0x9c);
  backBoxStyle.body.grad_color = LV_COLOR_MAKE(0x9c, 0x9c, 0x9c);
  static lv_style_t backBoxStylePR;
  lv_style_copy(&backBoxStylePR, &sideBoxStyle);
  backBoxStylePR.body.main_color = LV_COLOR_MAKE(0x5e, 0x5e, 0x5e);
  backBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x5e, 0x5e, 0x5e);

  setupButton(leftBox, 2, LV_HOR_RES / 2, LV_VER_RES, 5, 0, 0);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(leftBox, LV_BTN_STYLE_REL, &leftBoxStyle);
  lv_btn_set_style(leftBox, LV_BTN_STYLE_PR, &leftBoxStylePR);

  lv_label_set_text(leftBoxLabel, "LEFT");

  setupButton(rightBox, 3, LV_HOR_RES / 2, LV_VER_RES, 5, LV_HOR_RES / 2, 0);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(rightBox, LV_BTN_STYLE_REL, &rightBoxStyle);
  lv_btn_set_style(rightBox, LV_BTN_STYLE_PR, &rightBoxStylePR);

  lv_label_set_text(rightBoxLabel, "RIGHT");

  setupButton(backBox, 4, LV_HOR_RES / 4, LV_VER_RES/6, 5,( 3 * LV_HOR_RES / 8), (LV_VER_RES - LV_VER_RES/6));

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(backBox, LV_BTN_STYLE_REL, &backBoxStyle);
  lv_btn_set_style(backBox, LV_BTN_STYLE_PR, &backBoxStylePR);

  lv_label_set_text(backBoxLabel, "BACK");
}


void initAuton()
{
  static lv_style_t autonBoxStyle;
  lv_style_copy(&autonBoxStyle, &lv_style_plain);
  autonBoxStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  autonBoxStyle.body.border.width = 5;
  autonBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  static lv_style_t smallBoxStyle;
  lv_style_copy(&smallBoxStyle, &autonBoxStyle);
  smallBoxStyle.body.main_color = LV_COLOR_MAKE(0xbf,  0xbf, 0x00);
  smallBoxStyle.body.grad_color = LV_COLOR_MAKE(0xbf,  0xbf, 0x00);
  static lv_style_t smallBoxStylePR;
  lv_style_copy(&smallBoxStylePR, &autonBoxStyle);
  smallBoxStylePR.body.main_color = LV_COLOR_MAKE(0x99, 0x99, 0x00);
  smallBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x99, 0x99, 0x00);
  static lv_style_t medBoxStyle;
  lv_style_copy(&medBoxStyle, &autonBoxStyle);
  medBoxStyle.body.main_color = LV_COLOR_MAKE(0xc2, 0x4a, 0x00);
  medBoxStyle.body.grad_color = LV_COLOR_MAKE(0xc2, 0x4a, 0x00);
  static lv_style_t medBoxStylePR;
  lv_style_copy(&medBoxStylePR, &autonBoxStyle);
  medBoxStylePR.body.main_color = LV_COLOR_MAKE(0x9c, 0x3c, 0x00);
  medBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x9c, 0x3c, 0x00);
  static lv_style_t bigBoxStyle;
  lv_style_copy(&bigBoxStyle, &autonBoxStyle);
  bigBoxStyle.body.main_color = LV_COLOR_MAKE(0xc4, 0x00, 0x00);
  bigBoxStyle.body.grad_color = LV_COLOR_MAKE(0xc4, 0x00, 0x00);
  static lv_style_t bigBoxStylePR;
  lv_style_copy(&bigBoxStylePR, &autonBoxStyle);
  bigBoxStylePR.body.main_color = LV_COLOR_MAKE(0xab, 0x00, 0x00);
  bigBoxStylePR.body.grad_color = LV_COLOR_MAKE(0xab, 0x00, 0x00);

  static lv_style_t backBoxStyle2;
  lv_style_copy(&backBoxStyle2, &autonBoxStyle);
  backBoxStyle2.body.main_color = LV_COLOR_MAKE(0x9c, 0x9c, 0x9c);
  backBoxStyle2.body.grad_color = LV_COLOR_MAKE(0x9c, 0x9c, 0x9c);
  static lv_style_t backBoxStylePR2;
  lv_style_copy(&backBoxStylePR2, &autonBoxStyle);
  backBoxStylePR2.body.main_color = LV_COLOR_MAKE(0x5e, 0x5e, 0x5e);
  backBoxStylePR2.body.grad_color = LV_COLOR_MAKE(0x5e, 0x5e, 0x5e);

  setupButton(smallBox, 5, LV_HOR_RES / 3, LV_VER_RES, 5, 0, 0);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(smallBox, LV_BTN_STYLE_REL, &smallBoxStyle);
  lv_btn_set_style(smallBox, LV_BTN_STYLE_PR, &smallBoxStylePR);

  lv_label_set_text(smallBoxLabel, "SMALL");

  setupButton(medBox, 6, LV_HOR_RES / 3, LV_VER_RES, 5, LV_HOR_RES / 3, 0);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(medBox, LV_BTN_STYLE_REL, &medBoxStyle);
  lv_btn_set_style(medBox, LV_BTN_STYLE_PR, &medBoxStylePR);

  lv_label_set_text(medBoxLabel, "MED");

  setupButton(bigBox, 7, LV_HOR_RES / 3, LV_VER_RES, 5, (2 * LV_HOR_RES / 3), 0);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bigBox, LV_BTN_STYLE_REL, &bigBoxStyle);
  lv_btn_set_style(bigBox, LV_BTN_STYLE_PR, &bigBoxStylePR);

  lv_label_set_text(bigBoxLabel, "BIG");

  setupButton(backBox2, 8, LV_HOR_RES / 4, LV_VER_RES/6, 5,( 3 * LV_HOR_RES / 8), (LV_VER_RES - LV_VER_RES/6));

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(backBox2, LV_BTN_STYLE_REL, &backBoxStyle2);
  lv_btn_set_style(backBox2, LV_BTN_STYLE_PR, &backBoxStylePR2);

  lv_label_set_text(backBoxLabel2, "BACK");
}

void initialize()
{
  lv_init();
  initPrac();
  initSide();
  initAuton();
  loadScreen();

  FL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  FR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  BL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  BR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  Flywheel.set_brake_mode(E_MOTOR_BRAKE_COAST);
  Lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  RArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);


}

void disabled() {}

void competition_initialize() {}
