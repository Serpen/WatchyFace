#include "WatchyFace.h"
//#include "kw.cpp"

//WatchyFace::WatchyFace() {};

void WatchyFace::drawWatchFace()
{
  display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
  display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
  drawTime();
  drawDate();

  display.setFont(&DSEG7_Classic_Bold_25);
  drawSteps();
  drawSGDay();
  drawKW();
  drawBattery();
  display.drawBitmap(116, 75, WIFI_CONFIGURED ? wifi : wifioff, 26, 18, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
}

void WatchyFace::drawTime()
{
  display.setFont(&DSEG7_Classic_Bold_53);
  display.setCursor(5, 53 + 5);
  const uint8_t displayHour = currentTime.Hour;
  if (displayHour < 10)
    display.print("0");
  display.print(displayHour);
  display.print(":");
  if (currentTime.Minute < 10)
    display.print("0");
  display.println(currentTime.Minute);
}

void WatchyFace::drawDate()
{
  display.setFont(&Seven_Segment10pt7b);

  int16_t x1, y1;
  uint16_t w, h;

  const String dayOfWeek = dayStr(currentTime.Wday);
  display.getTextBounds(dayOfWeek, 5, 85, &x1, &y1, &w, &h);
  if (currentTime.Wday == 4) // Wed is long
    w -= 5;
  display.setCursor(85 - w, 85);
  display.println(dayOfWeek);

  const String month = monthShortStr(currentTime.Month);
  display.getTextBounds(month, 60, 110, &x1, &y1, &w, &h);
  display.setCursor(85 - w, 110);
  display.println(month);

  display.setFont(&DSEG7_Classic_Bold_25);
  display.setCursor(5, 120);
  if (currentTime.Day < 10)
    display.print("0");
  display.println(currentTime.Day);
}

void WatchyFace::drawSGDay()
{
  display.setCursor(5, 150);
#ifdef WATCHY_SIM
  const time_t mynow = time(0);
  const auto SECS_PER_HOUR = ((time_t)(3600UL));
  const auto SECS_PER_DAY = ((time_t)(SECS_PER_HOUR * 24UL));
#else
  const time_t mynow = makeTime(currentTime);
#endif
  
  const uint16_t sgd = ((mynow - Y1998) / SECS_PER_DAY) % 10000;
  display.println(sgd);
}

void WatchyFace::drawKW()
{
  uint8_t kw = getISOWeek(currentTime);
  
  display.drawRect(119, 111, 22, 22, GxEPD_BLACK);
  display.drawBitmap(120, 110, week, 20, 20, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
  display.setCursor(143, 133);
  display.println(kw);
}

void WatchyFace::drawSteps()
{
  // reset step counter in the night
  if (currentTime.Hour == 3 && currentTime.Minute == 0)
    sensor.resetStepCounter();
  const uint32_t stepCount = sensor.getCounter();
  display.drawBitmap(10, 165, steps, 19, 23, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
  display.setCursor(35, 190);
  display.println(stepCount); 
}

void WatchyFace::drawBattery()
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
