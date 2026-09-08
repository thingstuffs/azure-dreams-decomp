#include "common.h"

extern void *D_800814A8;

/* Updates the target offset from the global byte when it differs from the record value. */
void func_800DC168(void *record, void *owner) {
    u8 current_value;

       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    current_value = *((u8 *)D_800814A8 + 0x29);
    if (current_value != *((s32 *)record + 5)) {
        void *target;
        register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        target = *((void **)owner + 1);
        if (current_value < 0x80U) {
            value = -(s32)current_value;
            value /= 2;
            value -= 1;
        } else {
               /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            value = -0x40;
        }
        *((s16 *)target + 4) = value;
    }
}
