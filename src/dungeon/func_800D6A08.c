#include "common.h"

extern void *D_800814A8;

/* Updates the target offset from the global byte when it differs from the record value. */
void func_800DC168(void *record, void *owner) {
    u8 current_value;

    current_value = *((u8 *)D_800814A8 + 0x29);
    if (current_value != *((s32 *)record + 5)) {
        s16 *target;

        target = *((void **)owner + 1);
        if (current_value < 0x80U) {
            target[4] = -(s32)current_value / 2 - 1;
        } else {
            target[4] = -0x40;
        }
    }
}
