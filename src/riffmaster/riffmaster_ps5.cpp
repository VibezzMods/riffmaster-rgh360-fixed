#include "riffmaster_ps5.h"

#define RPT_BUTTONS1  8
#define RPT_BUTTONS2  9
#define RPT_BUTTONS3 10
#define RPT_WHAMMY   41
#define RPT_TILT     42

void ParseRiffmasterPS5(const uint8_t* report, size_t len, GuitarState* out)
{
    if (!report || len < 43 || report[0] != 0x01) {
        memset(out, 0, sizeof(GuitarState));
        return;
    }

    memset(out, 0, sizeof(GuitarState));

    uint8_t b8 = report[RPT_BUTTONS1];
    uint8_t b9 = report[RPT_BUTTONS2];
    uint8_t b10 = report[RPT_BUTTONS3];

    // Main frets
    if (b8 & 0x20) out->green = true;
    if (b8 & 0x40) out->red = true;
    if (b8 & 0x80) out->yellow = true;
    if (b8 & 0x10) out->blue = true;
    if (b9 & 0x01) out->orange = true;

    // Solo frets flag
    if (b9 & 0x40) out->solo = true;

    // Strum (hat nibble)
    uint8_t hat = b8 & 0x0F;
    out->strum_up = (hat == 0x00);
    out->strum_down = (hat == 0x04);

    // System buttons
    if (b9 & 0x20)  out->start = true;   // Start
    if (b9 & 0x10)  out->select = true;   // Options / Back
    if (b10 & 0x01) out->guide = true;   // PS logo -> Xbox button

    // Analog
    out->whammy = report[RPT_WHAMMY];
    out->tilt = report[RPT_TILT];
}