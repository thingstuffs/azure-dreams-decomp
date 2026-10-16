#include "common.h"

extern void townSelectDataForConditionD83(s32, s32, s32);
extern void townApplyEntryPosition(s32 *, s32 *, s32, s32);
extern s32 D_8001B920[];
extern s32 D_8001B964[];
extern s32 D_8001B994[];
extern s32 D_8001C358[];

/* Dispatch a code using the active table, with special handling for code 0x3E. */
void townDispatchActiveCode(s32 value, s32 special_value, s32 code) {
    s32 *active_table;

    if (D_8001B920[0] != 0) {
        active_table = D_8001B994;
    } else {
        active_table = D_8001B964;
    }
    if ((u32)(code - 0x40) < 3U) {
        D_8001B920[0] = 1;
    }
    if (code != 0x3E) {
        townApplyEntryPosition(active_table, D_8001C358, value, code);
    } else {
        townSelectDataForConditionD83(value, special_value, 0x3E);
    }
}
