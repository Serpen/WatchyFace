#include <Watchy.h>
#include "kw.h"

bool isLeapYear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

// Unix-Timestamp → Jahr, Monat, Tag
void unixToDate(time_t timestamp, int &year, int &month, int &day) {
  year = 1970;
  unsigned long days = timestamp / 86400;

  while (true) {
    int daysInYear = isLeapYear(year) ? 366 : 365;
    if (days >= daysInYear) {
      days -= daysInYear;
      year++;
    } else break;
  }

  month = 0;
  while (true) {
    int dim = daysInMonth[month];
    if (month == 1 && isLeapYear(year)) dim++; // Februar in Schaltjahr
    if (days >= dim) {
      days -= dim;
      month++;
    } else break;
  }

  day = days + 1;
  month += 1; // für Lesbarkeit (1–12)
}

// Wochentag berechnen (ISO: Montag = 1, Sonntag = 7)
int getWeekday(int year, int month, int day) {
  if (month < 3) {
    month += 12;
    year--;
  }
  int k = year % 100;
  int j = year / 100;
  int h = (day + 13*(month + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
  int d = ((h + 5) % 7) + 1; // ISO-Format: Montag = 1
  return d;
}

// Tag im Jahr berechnen (1–365/366)
int getDayOfYear(int year, int month, int day) {
  int doy = day;
  for (int i = 0; i < month - 1; i++) {
    doy += daysInMonth[i];
    if (i == 1 && isLeapYear(year)) doy++; // Februar
  }
  return doy;
}

// ISO-Woche berechnen aus Unix-Zeitstempel
int getISOWeek(time_t ts) {
  int year, month, day;
  unixToDate(ts, year, month, day);

  int weekday = getWeekday(year, month, day); // ISO: Montag=1
  int yday = getDayOfYear(year, month, day);

  // ISO-Formel: Woche = (TagImJahr - TagDerWoche + 10) / 7
  int week = (yday - weekday + 10) / 7;
  if (week < 1) week = 1; // Minimal absichern

  return week;
}