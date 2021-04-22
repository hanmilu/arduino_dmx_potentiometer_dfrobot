#include <Wire.h>
#include "DFRobot_RGBLCD.h"
#include <Conceptinetics.h>
#include <HSBColor.h>

int r,g,b;
int t=0;

DFRobot_RGBLCD lcd(16,2);  //16 characters and 2 lines of show
DMX_Master dmx_master (12, 2);

void setup() {
  // initialize
  lcd.init();
  dmx_master.enable();
}

void loop() {
  int val, val2, val3;
  int val4;
  int rgb[3];
  
  val=analogRead(0);
  val2=analogRead(1);
  val3=analogRead(2);
  val4=analogRead(3);

  val = 1023 - val;
  val2 = 1023 - val2;
  val3 = 1023 - val3;

  val = (float)((float)val / 1023.0) * 360.0;
  val2 = (float)((float)val2 / 1023.0) * 100.0;
  val3 = (float)((float)val3 / 1023.0) * 100.0;

  H2R_HSBtoRGB(val, val2, val3, rgb);
  
  val4 = 1023 - val4;
  val4 = val4 / 4;

  dmx_master.setChannelValue((uint16_t)4, (uint8_t)rgb[0]);
  dmx_master.setChannelValue((uint16_t)7, (uint8_t)rgb[0]);
  dmx_master.setChannelValue((uint16_t)10, (uint8_t)rgb[0]);
  
  dmx_master.setChannelValue((uint16_t)5, (uint8_t)rgb[1]);
  dmx_master.setChannelValue((uint16_t)8, (uint8_t)rgb[1]);
  dmx_master.setChannelValue((uint16_t)11, (uint8_t)rgb[1]);
  
  dmx_master.setChannelValue((uint16_t)6, (uint8_t)rgb[2]);
  dmx_master.setChannelValue((uint16_t)9, (uint8_t)rgb[2]);
  dmx_master.setChannelValue((uint16_t)12, (uint8_t)rgb[2]);

  //White
  dmx_master.setChannelValue((uint16_t)2, (uint8_t)val4);
  dmx_master.setChannelValue((uint16_t)3, (uint8_t)val4);
  
  lcd.setCursor(0,0);
  lcd.print("H:");
  lcd.print(val);
  lcd.print("/S:");
  lcd.print(val2);
  lcd.print("/          ");
  lcd.setCursor(0,1);
  lcd.print("/B:");
  lcd.print(val3);
  lcd.print("/W:");
  lcd.print(val4);
  lcd.print("/          ");

  delay(1);
}
