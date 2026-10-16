#include "common.h"

/* Maps an angle to one of four directions. */
s32 townMapAngleToCardinalDirection(s16 angle) {
    return ((s32) (0x400 - angle) >> 0xA) & 3;
}
