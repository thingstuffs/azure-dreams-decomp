#include "modules/dungeon_ovl_191284c.h"

s32 func_80024B3C(void) {
    s32 sign;

    sign = rand() & 1;
    if (sign == 0) {
        sign = -1;
    }
    return sign;
}
