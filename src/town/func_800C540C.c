#include "common.h"

/* Maps an angle to one of four directions. */
s32 func_800C2B6C(s16 angle) {
    return ((s32) (0x400 - angle) >> 0xA) & 3;
}
