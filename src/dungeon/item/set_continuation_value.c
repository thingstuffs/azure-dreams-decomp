#include "common.h"
#include "dungeon/item.h"

extern s32 D_800DCF60;

/* Sets the value stored in D_800DCF60. */
void set_continuation_value(s32 value) {
    D_800DCF60 = value;
}
