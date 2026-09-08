#include "common.h"

extern s32 D_80100DE0[];
extern s32 D_800D0C48[];

/* tcame_lock: Save and clear the two camera lock values. */
void func_800A50E0(void) {
    s32 lock_value_0;
    s32 lock_value_1;

    lock_value_0 = D_80100DE0[9];
    lock_value_1 = D_80100DE0[10];
    D_80100DE0[9] = 0;
    D_80100DE0[10] = 0;
    D_800D0C48[0] = lock_value_0;
    D_800D0C48[1] = lock_value_1;
}
