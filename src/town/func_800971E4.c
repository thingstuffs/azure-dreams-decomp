#include "common.h"
#include "m2c_compat.h"

M2C_UNK SD_Call();                     /* extern */
extern s32 D_800D0460;

/* Triggers event 0x519 at interval multiples when enabled. */
void func_80094944(s32 count, s32 interval) {
    if (((count % interval) == 0) && (D_800D0460 != 0)) {
        SD_Call(0x519);
    }
}
