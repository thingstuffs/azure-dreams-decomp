#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK D_80093BAC;
extern s32 *D_800FE5D8;

/* Sets D_800FE5D8 to point to D_80093BAC and returns zero. */
s32 set_hold_item_callback(void) {
    D_800FE5D8 = &D_80093BAC;
    return 0;
}
