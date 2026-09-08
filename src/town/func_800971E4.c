#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80053DA8();                     /* extern */
extern s32 D_800D0460;

/* Triggers event 0x519 at interval multiples when enabled. */
void func_80094944(s32 count, s32 interval) {
    if (((count % interval) == 0) && (D_800D0460 != 0)) {
        func_80053DA8(0x519);
    }
}
