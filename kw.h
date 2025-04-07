
// Anzahl Tage in jedem Monat (nicht-Schaltjahr)
const int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

bool isLeapYear(int year);

// Unix-Timestamp → Jahr, Monat, Tag
void unixToDate(unsigned long timestamp, int &year, int &month, int &day);

// Wochentag berechnen (ISO: Montag = 1, Sonntag = 7)
int getWeekday(int year, int month, int day);

// Tag im Jahr berechnen (1–365/366)
int getDayOfYear(int year, int month, int day);

// ISO-Woche berechnen aus Unix-Zeitstempel
int getISOWeek(unsigned long timestamp);