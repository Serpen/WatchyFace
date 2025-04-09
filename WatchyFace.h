#ifdef WATCHY_SIM
#include "..\..\Watchy.h"
#else // WATCHY_SIM
#include <Watchy.h>
#endif // WATCHY_SIM

#include <time.h>
#include "Seven_Segment10pt7b.h"
#include "DSEG7_Classic_Regular_15.h"
#include "DSEG7_Classic_Bold_25.h"
#include "DSEG7_Classic_Regular_39.h"
#include "icons.h"
#include "kw.h"

constexpr auto DARKMODE = false;
constexpr time_t Y1998 = 883609200;

constexpr uint8_t BATTERY_SEGMENT_WIDTH = 7;
constexpr uint8_t BATTERY_SEGMENT_HEIGHT = 11;
constexpr uint8_t BATTERY_SEGMENT_SPACING = 9;

class WatchyFace : public Watchy{
    using Watchy::Watchy;
    public:
        //WatchyFace();
        void drawWatchFace();
        void drawTime();
        void drawDate();
        void drawSteps();
        void drawSGDay();
        void drawKW();
        void drawBattery();
};
