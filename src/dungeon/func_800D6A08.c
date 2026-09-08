#include "common.h"

extern void *D_800814A8;

void func_800DC168(void *arg0, void *arg1) {
    u8 temp_v1;

       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    temp_v1 = *((u8 *)D_800814A8 + 0x29);
    if (temp_v1 != *((s32 *)arg0 + 5)) {
        void *temp_a1;
        register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        temp_a1 = *((void **)arg1 + 1);
        if (temp_v1 < 0x80U) {
            value = -(s32)temp_v1;
            value /= 2;
            value -= 1;
        } else {
               /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
            value = -0x40;
        }
        *((s16 *)temp_a1 + 4) = value;
    }
}
