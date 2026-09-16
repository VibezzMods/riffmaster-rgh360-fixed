#pragma once
#include <stdint.h>
#include <string.h>

struct GuitarState {
    bool green, red, yellow, blue, orange;
    bool strum_up, strum_down;
    bool solo;
    bool start, select, guide;
    uint8_t whammy;
    uint8_t tilt;
};

void ParseRiffmasterPS5(const uint8_t* report, size_t len, GuitarState* out);