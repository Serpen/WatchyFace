#include "kw.h"

const bool isLeapYear(uint16_t year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Tag im Jahr berechnen (1–365/366)
const uint16_t getDayOfYear(uint16_t year, uint8_t month, uint8_t day) {
  uint16_t doy = day;
  for (uint8_t i = 0; i < month - 1; i++) {
    doy += daysInMonth[i];
    if (i == 1 && isLeapYear(year)) doy++; // Februar
  }
  return doy;
}

// ISO-Woche berechnen aus Unix-Zeitstempel
const uint8_t getISOWeek(tmElements_t timestamp) {
    const uint16_t yday = getDayOfYear(timestamp.Year + YEAR_OFFSET, timestamp.Month, timestamp.Day);

    // ISO-Formel: Woche = (TagImJahr - TagDerWoche + 10) / 7
    uint8_t week = (yday - timestamp.Wday + 10) / 7;
    if (week < 1) week = 1; // Minimal absichern

    return week;
}