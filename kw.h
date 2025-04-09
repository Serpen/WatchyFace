#ifndef KWH
#define KWH

#ifdef WATCHY_SIM
#include "..\..\Watchy.h"
#else // WATCHY_SIM
#include <Watchy.h>
#endif // WATCHY_SIM

#include <time.h>

// Anzahl Tage in jedem Monat (nicht-Schaltjahr)
const uint8_t daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

const bool isLeapYear(uint16_t year);

// Tag im Jahr berechnen (1–365/366)
const uint16_t getDayOfYear(uint16_t year, uint8_t month, uint8_t day);

const uint8_t getISOWeek(tmElements_t timestamp);

#endif