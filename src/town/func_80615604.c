#include "common.h"

extern s32 func_80018CC0(void);
extern s32 D_80019144[];

/* Return the indexed table value, using entry 40 for indices of 41 or greater. */
s32 func_80016E04(void) {
    s32 index = func_80018CC0();
    s32 *value_table = D_80019144;
    s32 *value_entry;

    if (index < 0x29) {
        value_entry = &value_table[index];
    } else {
        value_entry = &value_table[40];
    }
    return *value_entry;
}
