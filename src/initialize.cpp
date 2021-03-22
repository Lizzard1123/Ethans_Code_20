// there is no way in hell this is gonna get clean
#include "custom/autonomous.h"
#include "custom/lizzardImg.h"

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

lv_obj_t *scrAuton = lv_obj_create(NULL, NULL);

lv_obj_t *smallBox = lv_btn_create(scrAuton, NULL);

lv_obj_t *smallBoxLabel = lv_label_create(smallBox, NULL);

lv_obj_t *medBox = lv_btn_create(scrAuton, NULL);

lv_obj_t *medBoxLabel = lv_label_create(medBox, NULL);

lv_obj_t *bigBox = lv_btn_create(scrAuton, NULL);

lv_obj_t *bigBoxLabel = lv_label_create(bigBox, NULL);

lv_obj_t *scrConf = lv_obj_create(NULL, NULL);

lv_obj_t *topBox = lv_btn_create(scrColor, NULL);

lv_obj_t *topBoxLabel = lv_label_create(topBox, NULL);

lv_obj_t *topMidBox = lv_btn_create(scrColor, NULL);

lv_obj_t *topMidBoxLabel = lv_label_create(topMidBox, NULL);

lv_obj_t *bottomMidBox = lv_btn_create(scrColor, NULL);

lv_obj_t *bottomMidBoxLabel = lv_label_create(bottomMidBox, NULL);

lv_obj_t *bottomBox = lv_btn_create(scrColor, NULL);

lv_obj_t *bottomBoxLabel = lv_label_create(bottomBox, NULL);

lv_obj_t *topBox2 = lv_btn_create(scrSide, NULL);

lv_obj_t *topBoxLabel2 = lv_label_create(topBox2, NULL);

lv_obj_t *topMidBox2 = lv_btn_create(scrSide, NULL);

lv_obj_t *topMidBoxLabel2 = lv_label_create(topMidBox2, NULL);

lv_obj_t *bottomMidBox2 = lv_btn_create(scrSide, NULL);

lv_obj_t *bottomMidBoxLabel2 = lv_label_create(bottomMidBox2, NULL);

lv_obj_t *bottomBox2 = lv_btn_create(scrSide, NULL);

lv_obj_t *bottomBoxLabel2 = lv_label_create(bottomBox2, NULL);

lv_obj_t *topBox3 = lv_btn_create(scrAuton, NULL);

lv_obj_t *topBoxLabel3 = lv_label_create(topBox3, NULL);

lv_obj_t *topMidBox3 = lv_btn_create(scrAuton, NULL);

lv_obj_t *topMidBoxLabel3 = lv_label_create(topMidBox3, NULL);

lv_obj_t *bottomMidBox3 = lv_btn_create(scrAuton, NULL);

lv_obj_t *bottomMidBoxLabel3 = lv_label_create(bottomMidBox3, NULL);

lv_obj_t *bottomBox3 = lv_btn_create(scrAuton, NULL);

lv_obj_t *bottomBoxLabel3 = lv_label_create(bottomBox3, NULL);

lv_obj_t *topBox4 = lv_btn_create(scrConf, NULL);

lv_obj_t *topBoxLabel4 = lv_label_create(topBox4, NULL);

lv_obj_t *topMidBox4 = lv_btn_create(scrConf, NULL);

lv_obj_t *topMidBoxLabel4 = lv_label_create(topMidBox4, NULL);

lv_obj_t *bottomMidBox4 = lv_btn_create(scrConf, NULL);

lv_obj_t *bottomMidBoxLabel4 = lv_label_create(bottomMidBox4, NULL);

lv_obj_t *bottomBox4 = lv_btn_create(scrConf, NULL);

lv_obj_t *bottomBoxLabel4 = lv_label_create(bottomBox4, NULL);

lv_obj_t *infoBox1 = lv_obj_create(scrConf, NULL);

lv_obj_t *infoBoxChild1 = lv_obj_create(infoBox1, NULL);

lv_obj_t *infoBoxLabel1 = lv_label_create(infoBoxChild1, NULL);

lv_obj_t *infoBox2 = lv_obj_create(scrConf, NULL);

lv_obj_t *infoBoxChild2 = lv_obj_create(infoBox2, NULL);

lv_obj_t *infoBoxLabel2 = lv_label_create(infoBoxChild2, NULL);

lv_obj_t *infoBox3 = lv_obj_create(scrConf, NULL);

lv_obj_t *infoBoxChild3 = lv_obj_create(infoBox3, NULL);

lv_obj_t *infoBoxLabel3 = lv_label_create(infoBoxChild3, NULL);

lv_obj_t *doneBtn = lv_btn_create(scrConf, NULL);

lv_obj_t *doneBtnLabel = lv_label_create(doneBtn, NULL);

lv_obj_t *scrReg = lv_obj_create(NULL, NULL);

lv_obj_t *img1 = lv_img_create(scrReg, NULL);

LV_IMG_DECLARE(BongoLizzard);

lv_obj_t *colorInfo = lv_obj_create(scrReg, NULL);

lv_obj_t *debugBtn = lv_btn_create(scrReg, NULL);

lv_obj_t *debugBtnLabel = lv_label_create(debugBtn, NULL);

lv_obj_t *scrDebug = lv_obj_create(NULL, NULL);

lv_obj_t *returnBtn = lv_btn_create(scrDebug, NULL);

lv_obj_t *returnBtnLabel = lv_label_create(returnBtn, NULL);

lv_obj_t *debugX = lv_obj_create(scrDebug, NULL);

lv_obj_t *debugXLabel = lv_label_create(debugX, NULL);

lv_obj_t *debugY = lv_obj_create(scrDebug, NULL);

lv_obj_t *debugYLabel = lv_label_create(debugY, NULL);

bool colorSelected = false;
bool sideSelected = false;
bool autonSelected = false;

bool allSet()
{
  return colorSelected && sideSelected && autonSelected;
}

void updateConf()
{
  if (colorSelected)
  {
    bool boolBlue = Bongo.getColor();
    lv_label_set_text(infoBoxLabel1, boolBlue ? "Blue" : "Red");
    if (boolBlue)
    {
      static lv_style_t infoOneBlue;
      lv_style_copy(&infoOneBlue, &lv_style_plain);
      infoOneBlue.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoOneBlue.body.border.width = 5;
      infoOneBlue.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoOneBlue.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
      infoOneBlue.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
      lv_obj_set_style(infoBox1, &infoOneBlue);
    }
    else
    {
      static lv_style_t infoOneRed;
      lv_style_copy(&infoOneRed, &lv_style_plain);
      infoOneRed.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoOneRed.body.border.width = 5;
      infoOneRed.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoOneRed.body.main_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
      infoOneRed.body.grad_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
      lv_obj_set_style(infoBox1, &infoOneRed);
    }
  }
  if (sideSelected)
  {
    bool boolLeft = Bongo.getSide();
    lv_label_set_text(infoBoxLabel2, boolLeft ? "Left" : "Right");
    if (boolLeft)
    {
      static lv_style_t infoTwoLeft;
      lv_style_copy(&infoTwoLeft, &lv_style_plain);
      infoTwoLeft.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoTwoLeft.body.border.width = 5;
      infoTwoLeft.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoTwoLeft.body.main_color = LV_COLOR_MAKE(0x00, 0x96, 0x0f);
      infoTwoLeft.body.grad_color = LV_COLOR_MAKE(0x00, 0x96, 0x0f);
      lv_obj_set_style(infoBox2, &infoTwoLeft);
    }
    else
    {
      static lv_style_t infoTwoRight;
      lv_style_copy(&infoTwoRight, &lv_style_plain);
      infoTwoRight.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoTwoRight.body.border.width = 5;
      infoTwoRight.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoTwoRight.body.main_color = LV_COLOR_MAKE(0xe0, 0x52, 0xc8);
      infoTwoRight.body.grad_color = LV_COLOR_MAKE(0xe0, 0x52, 0xc8);
      lv_obj_set_style(infoBox2, &infoTwoRight);
    }
  }
  if (autonSelected)
  {
    bool isOne = Bongo.getAutonNum() == 1;
    bool isTwo = Bongo.getAutonNum() == 2;
    lv_label_set_text(infoBoxLabel3, isOne ? "Small" : isTwo == 2 ? "Med" : "Big");
    if (isOne)
    {
      static lv_style_t infoThreeSmall;
      lv_style_copy(&infoThreeSmall, &lv_style_plain);
      infoThreeSmall.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoThreeSmall.body.border.width = 5;
      infoThreeSmall.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoThreeSmall.body.main_color = LV_COLOR_MAKE(0xbf, 0xbf, 0x00);
      infoThreeSmall.body.grad_color = LV_COLOR_MAKE(0xbf, 0xbf, 0x00);
      lv_obj_set_style(infoBox3, &infoThreeSmall);
    }
    else if (isTwo)
    {
      static lv_style_t infoThreeMed;
      lv_style_copy(&infoThreeMed, &lv_style_plain);
      infoThreeMed.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoThreeMed.body.border.width = 5;
      infoThreeMed.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoThreeMed.body.main_color = LV_COLOR_MAKE(0xc2, 0x4a, 0x00);
      infoThreeMed.body.grad_color = LV_COLOR_MAKE(0xc2, 0x4a, 0x00);
      lv_obj_set_style(infoBox3, &infoThreeMed);
    }
    else
    {
      static lv_style_t infoThreeBig;
      lv_style_copy(&infoThreeBig, &lv_style_plain);
      infoThreeBig.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoThreeBig.body.border.width = 5;
      infoThreeBig.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
      infoThreeBig.body.main_color = LV_COLOR_MAKE(0xc4, 0x00, 0x00);
      infoThreeBig.body.grad_color = LV_COLOR_MAKE(0xc4, 0x00, 0x00);
      lv_obj_set_style(infoBox3, &infoThreeBig);
    }
  }

  lv_obj_refresh_style(infoBox1);
  lv_obj_refresh_style(infoBox2);
  lv_obj_refresh_style(infoBox3);
}

void updateColor()
{
  if (Bongo.getColor())
  {
    static lv_style_t colorInfoBlueStyle;
    lv_style_copy(&colorInfoBlueStyle, &lv_style_plain);
    colorInfoBlueStyle.body.main_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
    colorInfoBlueStyle.body.grad_color = LV_COLOR_MAKE(0x00, 0x00, 0xc8);
    lv_obj_set_style(colorInfo, &colorInfoBlueStyle);
  }
  else
  {
    static lv_style_t colorInfoRedStyle;
    lv_style_copy(&colorInfoRedStyle, &lv_style_plain);
    colorInfoRedStyle.body.main_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
    colorInfoRedStyle.body.grad_color = LV_COLOR_MAKE(0xc8, 0x00, 0x00);
    lv_obj_set_style(colorInfo, &colorInfoRedStyle);
  }
}

int current = 0;
void loadScreen(int num = current)
{
  switch (num)
  {
  case 0:
    lv_scr_load(scrColor);
    break;
  case 1:
    lv_scr_load(scrSide);
    break;
  case 2:
    lv_scr_load(scrAuton);
    break;
  case 3:
    updateConf();
    lv_scr_load(scrConf);
    break;
  case 4:
    updateColor();
    lv_scr_load(scrReg);
    break;
  case 5:
    lv_scr_load(scrDebug);
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
    colorSelected = true;
    Bongo.setRed();
    lv_label_set_text(redBoxLabel, "    RED\n(SELECTED)");
    lv_label_set_text(blueBoxLabel, "BLUE");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 1: // Blue button
    colorSelected = true;
    Bongo.setBlue();
    lv_label_set_text(blueBoxLabel, "    BLUE \n(SELECTED)");
    lv_label_set_text(redBoxLabel, "RED");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 2: // left button
    sideSelected = true;
    Bongo.sideIsLeft(true);
    lv_label_set_text(leftBoxLabel, "    LEFT \n(SELECTED)");
    lv_label_set_text(rightBoxLabel, "RIGHT");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 3: // right button
    sideSelected = true;
    Bongo.sideIsLeft(false);
    lv_label_set_text(rightBoxLabel, "    RIGHT \n(SELECTED)");
    lv_label_set_text(leftBoxLabel, "LEFT");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 4:

    break;

  case 5: // small button
    autonSelected = true;
    Bongo.setAutonNum(1);
    lv_label_set_text(smallBoxLabel, "   SMALL \n(SELECTED)");
    lv_label_set_text(medBoxLabel, "MED");
    lv_label_set_text(bigBoxLabel, "BIG");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 6: // med button
    autonSelected = true;
    Bongo.setAutonNum(2);
    lv_label_set_text(medBoxLabel, "    MED \n(SELECTED)");
    lv_label_set_text(smallBoxLabel, "SMALL");
    lv_label_set_text(bigBoxLabel, "BIG");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 7: // big button
    autonSelected = true;
    Bongo.setAutonNum(3);
    lv_label_set_text(bigBoxLabel, "     BIG \n(SELECTED)");
    lv_label_set_text(medBoxLabel, "MED");
    lv_label_set_text(smallBoxLabel, "SMALL");
    delay(interval);
    current++;
    loadScreen();
    break;

  case 8: //

    break;

  case 9: // red button

    break;

  case 10: // color button
    current = 0;
    loadScreen(0);
    break;

  case 11: // side button
    current = 1;
    loadScreen(1);
    break;

  case 12: // auton button
    current = 2;
    loadScreen(2);
    break;

  case 13: // confirm button
    current = 3;
    loadScreen(3);
    break;
  case 14: //

    break;
  case 15: //Done btn
    if (allSet())
    {
      current = 4;
      loadScreen(4);
    }

    break;
  case 16: // debug screen
    current = 5;
    loadScreen(5);
    break;
  case 17: // return btn
    current = 4;
    loadScreen(4);
    break;
  case 18: //

    break;
  case 19: //

    break;
  case 20: //

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

int offset = 5;

void initColor()
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

  setupButton(redBox, 0, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES - 2 * offset, 5, LV_HOR_RES / 4 + offset, offset);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(redBox, LV_BTN_STYLE_REL, &redBoxStyle);
  lv_btn_set_style(redBox, LV_BTN_STYLE_PR, &redBoxStylePR);

  lv_label_set_text(redBoxLabel, "RED");

  setupButton(blueBox, 1, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES - 2 * offset, 5, (5 * LV_HOR_RES / 8) + offset, offset);

  // redBoxStyle, redBoxStylePR
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

  setupButton(leftBox, 2, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES - 2 * offset, 5, LV_HOR_RES / 4 + offset, offset);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(leftBox, LV_BTN_STYLE_REL, &leftBoxStyle);
  lv_btn_set_style(leftBox, LV_BTN_STYLE_PR, &leftBoxStylePR);

  lv_label_set_text(leftBoxLabel, "LEFT");

  setupButton(rightBox, 3, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES - 2 * offset, 5, (5 * LV_HOR_RES / 8) + offset, offset);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(rightBox, LV_BTN_STYLE_REL, &rightBoxStyle);
  lv_btn_set_style(rightBox, LV_BTN_STYLE_PR, &rightBoxStylePR);

  lv_label_set_text(rightBoxLabel, "RIGHT");
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
  smallBoxStyle.body.main_color = LV_COLOR_MAKE(0xbf, 0xbf, 0x00);
  smallBoxStyle.body.grad_color = LV_COLOR_MAKE(0xbf, 0xbf, 0x00);
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

  setupButton(smallBox, 5, (LV_HOR_RES / 4) - 2 * offset, LV_VER_RES - 2 * offset, 5, (LV_HOR_RES / 4) + offset, offset);

  // redBoxStyle, redBoxStylePR
  lv_btn_set_style(smallBox, LV_BTN_STYLE_REL, &smallBoxStyle);
  lv_btn_set_style(smallBox, LV_BTN_STYLE_PR, &smallBoxStylePR);

  lv_label_set_text(smallBoxLabel, "SMALL");

  setupButton(medBox, 6, (LV_HOR_RES / 4) - 2 * offset, LV_VER_RES - 2 * offset, 5, (LV_HOR_RES / 2) + offset, offset);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(medBox, LV_BTN_STYLE_REL, &medBoxStyle);
  lv_btn_set_style(medBox, LV_BTN_STYLE_PR, &medBoxStylePR);

  lv_label_set_text(medBoxLabel, "MED");

  setupButton(bigBox, 7, (LV_HOR_RES / 4) - 2 * offset, LV_VER_RES - 2 * offset, 5, (3 * LV_HOR_RES / 4) + offset, offset);

  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bigBox, LV_BTN_STYLE_REL, &bigBoxStyle);
  lv_btn_set_style(bigBox, LV_BTN_STYLE_PR, &bigBoxStylePR);

  lv_label_set_text(bigBoxLabel, "BIG");
}

void initSideBar()
{
  static lv_style_t sideBarBoxStyle;
  lv_style_copy(&sideBarBoxStyle, &lv_style_plain);
  sideBarBoxStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  sideBarBoxStyle.body.border.width = 5;
  sideBarBoxStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  sideBarBoxStyle.body.main_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  sideBarBoxStyle.body.grad_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  static lv_style_t sideBarBoxStylePR;
  lv_style_copy(&sideBarBoxStylePR, &lv_style_plain);
  sideBarBoxStylePR.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  sideBarBoxStylePR.body.border.width = 5;
  sideBarBoxStylePR.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  sideBarBoxStylePR.body.main_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);
  sideBarBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);

  setupButton(topBox, 10, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 0);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topBox, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topBox, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topBoxLabel, "Color");

  setupButton(topMidBox, 11, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topMidBox, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topMidBox, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topMidBoxLabel, "Side");

  setupButton(bottomMidBox, 12, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 2);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomMidBox, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomMidBox, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomMidBoxLabel, "Auton");

  setupButton(bottomBox, 13, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 3 * LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomBox, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomBox, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomBoxLabel, "Confirm");

  setupButton(topBox2, 10, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 0);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topBox2, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topBox2, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topBoxLabel2, "Color");

  setupButton(topMidBox2, 11, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topMidBox2, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topMidBox2, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topMidBoxLabel2, "Side");

  setupButton(bottomMidBox2, 12, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 2);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomMidBox2, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomMidBox2, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomMidBoxLabel2, "Auton");

  setupButton(bottomBox2, 13, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 3 * LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomBox2, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomBox2, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomBoxLabel2, "Confirm");

  setupButton(topBox3, 10, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 0);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topBox3, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topBox3, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topBoxLabel3, "Color");

  setupButton(topMidBox3, 11, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topMidBox3, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topMidBox3, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topMidBoxLabel3, "Side");

  setupButton(bottomMidBox3, 12, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 2);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomMidBox3, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomMidBox3, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomMidBoxLabel3, "Auton");

  setupButton(bottomBox3, 13, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 3 * LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomBox3, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomBox3, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomBoxLabel3, "Confirm");

  setupButton(topBox4, 10, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 0);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topBox4, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topBox4, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topBoxLabel4, "Color");

  setupButton(topMidBox4, 11, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(topMidBox4, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(topMidBox4, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(topMidBoxLabel4, "Side");

  setupButton(bottomMidBox4, 12, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, LV_VER_RES / 2);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomMidBox4, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomMidBox4, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomMidBoxLabel4, "Auton");

  setupButton(bottomBox4, 13, LV_HOR_RES / 4, LV_VER_RES / 4, 5, 0, 3 * LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(bottomBox4, LV_BTN_STYLE_REL, &sideBarBoxStyle);
  lv_btn_set_style(bottomBox4, LV_BTN_STYLE_PR, &sideBarBoxStylePR);

  lv_label_set_text(bottomBoxLabel4, "Confirm");
}

void initConf()
{
  static lv_style_t ConfBoxStylePlain;
  lv_style_copy(&ConfBoxStylePlain, &lv_style_plain);
  ConfBoxStylePlain.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  ConfBoxStylePlain.body.border.width = 5;
  ConfBoxStylePlain.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  static lv_style_t ConfBoxStyle;
  lv_style_copy(&ConfBoxStyle, &ConfBoxStylePlain);
  ConfBoxStyle.body.main_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  ConfBoxStyle.body.grad_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  static lv_style_t ConfBoxStylePR;
  lv_style_copy(&ConfBoxStylePR, &ConfBoxStylePlain);
  ConfBoxStylePR.body.main_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);
  ConfBoxStylePR.body.grad_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);

  static lv_style_t ConfBoxStylePlainInfo;
  lv_style_copy(&ConfBoxStylePlainInfo, &lv_style_plain);
  ConfBoxStylePlain.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);

  static lv_style_t ConfBoxStyle1;
  lv_style_copy(&ConfBoxStyle1, &ConfBoxStylePlainInfo);
  ConfBoxStyle1.body.main_color = LV_COLOR_MAKE(0xdc, 0xe0, 0xe0);
  ConfBoxStyle1.body.grad_color = LV_COLOR_MAKE(0xdc, 0xe0, 0xe0);

  static lv_style_t ConfBoxStyle2;
  lv_style_copy(&ConfBoxStyle2, &ConfBoxStylePlainInfo);
  ConfBoxStyle2.body.main_color = LV_COLOR_MAKE(0xdc, 0xe0, 0xe0);
  ConfBoxStyle2.body.grad_color = LV_COLOR_MAKE(0xdc, 0xe0, 0xe0);

  static lv_style_t ConfBoxStyle3;
  lv_style_copy(&ConfBoxStyle3, &ConfBoxStylePlainInfo);
  ConfBoxStyle3.body.main_color = LV_COLOR_MAKE(0xdc, 0xe0, 0xe0);
  ConfBoxStyle3.body.grad_color = LV_COLOR_MAKE(0xdc, 0xe0, 0xe0);

  lv_obj_set_size(infoBox1, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES / 2 - 2 * offset);
  lv_obj_set_pos(infoBox1, LV_HOR_RES / 4 + offset, offset);
  lv_label_set_text(infoBoxLabel1, "Select Color");
  lv_obj_set_style(infoBox1, &ConfBoxStyle1);

  lv_obj_set_size(infoBox2, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES / 2 - 2 * offset);
  lv_obj_set_pos(infoBox2, (5 * LV_HOR_RES / 8) + offset, offset);
  lv_label_set_text(infoBoxLabel2, "Select Side");
  lv_obj_set_style(infoBox2, &ConfBoxStyle2);

  lv_obj_set_size(infoBox3, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES / 2 - 2 * offset);
  lv_obj_set_pos(infoBox3, LV_HOR_RES / 4 + offset, LV_VER_RES / 2 + offset);
  lv_label_set_text(infoBoxLabel3, "Select Auton");
  lv_obj_set_style(infoBox3, &ConfBoxStyle3);

  setupButton(doneBtn, 15, (3 * LV_HOR_RES / 8) - 2 * offset, LV_VER_RES / 2 - 2 * offset, 5, (5 * LV_HOR_RES / 8) + offset, LV_VER_RES / 2 + offset);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(doneBtn, LV_BTN_STYLE_REL, &ConfBoxStyle);
  lv_btn_set_style(doneBtn, LV_BTN_STYLE_PR, &ConfBoxStylePR);

  lv_label_set_text(doneBtnLabel, "Done");

  static lv_style_t ConfBoxStylelabel;
  lv_style_copy(&ConfBoxStylelabel, &ConfBoxStylePlainInfo);
  ConfBoxStylelabel.body.opa = LV_OPA_TRANSP;
  ConfBoxStylelabel.body.border.width = 0;
  lv_obj_set_style(infoBoxChild1, &ConfBoxStylelabel);
  lv_obj_set_style(infoBoxChild2, &ConfBoxStylelabel);
  lv_obj_set_style(infoBoxChild3, &ConfBoxStylelabel);
  lv_obj_set_size(infoBoxChild1, 80, 20);
  lv_obj_set_size(infoBoxChild2, 80, 20);
  lv_obj_set_size(infoBoxChild3, 80, 20);
  lv_label_set_align(infoBoxLabel1, LV_LABEL_ALIGN_CENTER);
  lv_label_set_align(infoBoxLabel2, LV_LABEL_ALIGN_CENTER);
  lv_label_set_align(infoBoxLabel3, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(infoBoxChild1, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(infoBoxChild2, NULL, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(infoBoxChild3, NULL, LV_ALIGN_CENTER, 0, 0);
}

void initReg()
{
  static lv_style_t debugBtnStyle;
  lv_style_copy(&debugBtnStyle, &lv_style_plain);
  debugBtnStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  debugBtnStyle.body.border.width = 5;
  debugBtnStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  debugBtnStyle.body.main_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  debugBtnStyle.body.grad_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  static lv_style_t debugBtnStylePR;
  lv_style_copy(&debugBtnStylePR, &lv_style_plain);
  debugBtnStylePR.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  debugBtnStylePR.body.border.width = 5;
  debugBtnStylePR.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  debugBtnStylePR.body.main_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);
  debugBtnStylePR.body.grad_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);

  setupButton(debugBtn, 16, LV_VER_RES / 3, LV_VER_RES / 4, 5, LV_HOR_RES - LV_VER_RES / 3, 3 * LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(debugBtn, LV_BTN_STYLE_REL, &debugBtnStyle);
  lv_btn_set_style(debugBtn, LV_BTN_STYLE_PR, &debugBtnStylePR);

  lv_label_set_text(debugBtnLabel, "Debug");

  lv_obj_set_size(colorInfo, LV_HOR_RES, 20);
  lv_obj_set_pos(colorInfo, 0, 0);

  lv_img_set_src(img1, &BongoLizzard);
  lv_obj_set_pos(img1, 0, 20);
}

void initDebug(){
  static lv_style_t returnBtnStyle;
  lv_style_copy(&returnBtnStyle, &lv_style_plain);
  returnBtnStyle.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  returnBtnStyle.body.border.width = 5;
  returnBtnStyle.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  returnBtnStyle.body.main_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  returnBtnStyle.body.grad_color = LV_COLOR_MAKE(0x8a, 0x8a, 0x8a);
  static lv_style_t returnBtnStylePR;
  lv_style_copy(&returnBtnStylePR, &lv_style_plain);
  returnBtnStylePR.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  returnBtnStylePR.body.border.width = 5;
  returnBtnStylePR.body.border.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  returnBtnStylePR.body.main_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);
  returnBtnStylePR.body.grad_color = LV_COLOR_MAKE(0x52, 0x52, 0x52);

  setupButton(returnBtn, 17, LV_VER_RES / 3, LV_VER_RES / 4, 5, LV_HOR_RES - LV_VER_RES / 3, 3 * LV_VER_RES / 4);
  // blueBoxStyle, blueBoxStylePR,
  lv_btn_set_style(returnBtn, LV_BTN_STYLE_REL, &returnBtnStyle);
  lv_btn_set_style(returnBtn, LV_BTN_STYLE_PR, &returnBtnStylePR);

  lv_label_set_text(returnBtnLabel, "Return");
  static lv_style_t debugPlain;
  lv_style_copy(&debugPlain, &lv_style_plain);
  debugPlain.text.color = LV_COLOR_MAKE(0x00, 0x00, 0x00);
  debugPlain.body.main_color = LV_COLOR_MAKE(0xd1, 0xd1, 0xd1);
  debugPlain.body.grad_color = LV_COLOR_MAKE(0xd1, 0xd1, 0xd1);
  lv_obj_set_style(debugX, &debugPlain);
  lv_obj_set_style(debugY, &debugPlain);
  //debugs
  //four collums with 8 sections each
  lv_obj_set_size(debugX, LV_HOR_RES/4, LV_VER_RES/8);
  lv_obj_set_pos(debugX, 0, 0);
  lv_obj_set_size(debugY, LV_HOR_RES/4, LV_VER_RES/8);
  lv_obj_set_pos(debugY, 0, LV_VER_RES/8);
}

void blackBack(){
  static lv_style_t backgroundStyle;
  lv_style_copy(&backgroundStyle, &lv_style_plain);
  backgroundStyle.body.main_color = LV_COLOR_MAKE(0x38, 0x38, 0x38);
  backgroundStyle.body.grad_color = LV_COLOR_MAKE(0x38, 0x38, 0x38);
  backgroundStyle.body.border.width = 0;
  backgroundStyle.body.border.color = LV_COLOR_MAKE(0x38, 0x38, 0x38);

  lv_obj_set_style(scrColor, &backgroundStyle);
  lv_obj_set_style(scrSide, &backgroundStyle);
  lv_obj_set_style(scrAuton, &backgroundStyle);
  lv_obj_set_style(scrConf, &backgroundStyle);
  lv_obj_set_style(scrReg, &backgroundStyle);
  lv_obj_set_style(scrDebug, &backgroundStyle);
}

void initialize()
{
  Vincent.reset();
  delay(2000);
  while (Vincent.is_calibrating())
  {
    printf("Waitn");
    delay(10);
  }
  Bongo.initThreads();
  lv_init();
  initColor();
  initSide();
  initAuton();
  initConf();
  initReg();
  initDebug();
  initSideBar();
  blackBack();
  loadScreen();
  rightArm.calibrate();
  leftArm.calibrate();
  printf("Init pot \n");
  delay(250);
  FL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  FR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  BL.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  BR.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  Flywheel.set_brake_mode(E_MOTOR_BRAKE_COAST);
  Lift.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  LArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  RArm.set_brake_mode(E_MOTOR_BRAKE_BRAKE);
  outtakeSense.set_led_pwm(100);
  Police.set_led_pwm(100);
  EYES.set_signature(EYES__CUSTOM_GREEN_NUM, &EYES__CUSTOM_GREEN);
  Big_Brother.set_signature(Big_Brother_CUSTOMRED_SIG_NUM, &Big_Brother_CUSTOMRED_SIG);
  Big_Brother.set_signature(Big_Brother_CUSTOMBLUE_SIG_NUM, &Big_Brother_CUSTOMBLUE_SIG);
}

void disabled() {
  //Bongo.Movement.stopAll();
}

void competition_initialize() {}
