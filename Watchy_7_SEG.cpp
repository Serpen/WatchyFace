#include "Watchy_7_SEG.h"
#include "kw.h"

#define DARKMODE false
#define Y1998 883609200UL

const uint8_t BATTERY_SEGMENT_WIDTH = 7;
const uint8_t BATTERY_SEGMENT_HEIGHT = 11;
const uint8_t BATTERY_SEGMENT_SPACING = 9;

void Watchy7SEG::drawWatchFace()
{
  display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
  display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
  drawTime();
  drawDate();
  drawSteps();
  drawSGDay();
  drawKW();
  drawTemp();
  drawBattery();
  display.drawBitmap(116, 75, WIFI_CONFIGURED ? wifi : wifioff, 26, 18, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

void Watchy7SEG::drawTime()
{
  display.setFont(&DSEG7_Classic_Bold_53);
  display.setCursor(5, 53 + 5);
  int displayHour;
    displayHour = currentTime.Hour;
  if (displayHour < 12)
    display.print("0");
  display.print(displayHour);
  display.print(":");
  if (currentTime.Minute < 10)
    display.print("0");
  display.println(currentTime.Minute);
}

void Watchy7SEG::drawDate()
{
  display.setFont(&Seven_Segment10pt7b);

  int16_t x1, y1;
  uint16_t w, h;

  String dayOfWeek = dayStr(currentTime.Wday);
  display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
  if (currentTime.Wday == 4)
    w -= 5;
  display.setCursor(85 - w, 85);
  display.println(dayOfWeek);

  String month = monthShortStr(currentTime.Month);
  display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
  display.setCursor(85 - w, 110);
  display.println(month);

  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(5, 120);
  if (currentTime.Day < 10)
    display.print("0");
  display.println(currentTime.Day);
}

void Watchy7SEG::drawSGDay()
{
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(5, 150);
  time_t mynow = makeTime(currentTime);
  display.println(((mynow - Y1998) / SECS_PER_DAY) % 10000);
}

void Watchy7SEG::drawKW()
{
  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(145, 158);

  time_t tm =  makeTime(currentTime);
  int kw = getISOWeek(tm);
  display.print("KW ");
  display.print(kw);
}

void Watchy7SEG::drawTemp() {
  display.setFont(&DSEG7_Classic_Regular_39);
  
  uint8_t temperature = sensor.readTemperature();
  int16_t  x1, y1;
  uint16_t w, h;
  display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
  if(159 - w - x1 > 87){
      display.setCursor(159 - w - x1, 150);
  }else{
      display.setFont(&DSEG7_Classic_Bold_25);
      display.getTextBounds(String(temperature), 0, 0, &x1, &y1, &w, &h);
      display.setCursor(159 - w - x1, 136);
  }
  display.println(temperature);
}

void Watchy7SEG::drawSteps()
{
  // reset step counter in the night
  if (currentTime.Hour == 3 && currentTime.Minute == 0)
    sensor.resetStepCounter();
  uint32_t stepCount = sensor.getCounter();
  display.drawBitmap(10, 165, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
  display.setCursor(35, 190);
  display.println(stepCount);
}

void Watchy7SEG::drawBattery()
{
  display.drawBitmap(158, 73, battery, 37, 21, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
  display.fillRect(163, 78, 27, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE); // clear battery segments
  int8_t batteryLevel = 0;
  float VBAT = getBatteryVoltage();
  if (VBAT > 4.0)
    batteryLevel = 3;
  else if (VBAT > 3.6 && VBAT <= 4.0)
    batteryLevel = 2;
  else if (VBAT > 3.20 && VBAT <= 3.6)
    batteryLevel = 1;
  else if (VBAT <= 3.20)
    batteryLevel = 0;

  for (int8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++)
    display.fillRect(163 + (batterySegments * BATTERY_SEGMENT_SPACING), 78, BATTERY_SEGMENT_WIDTH, BATTERY_SEGMENT_HEIGHT, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}
