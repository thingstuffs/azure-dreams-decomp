#include "common.h"

extern u8 D_80016000[0x10];

extern void func_80018ADC(s32);
extern s32 func_80018B5C(s32);

/* Decrements the current entry's counter for 0x5C8, otherwise checks 0x11FC. */
s32 func_800173F0(void) {
    s32 result;

    if (func_80018B5C(0x5C8) != 0) {
        {
            void *context;
            u8 *entry;

            context = *(void **)D_80016000;
            entry = (u8 *)((*(s32 *)((u8 *)context + 8) << 3) + *(s32 *)((u8 *)context + 0x40));
            entry[1] -= 1;
        }
        result = 0;
        {
            void *context;
            u8 *entry;

            context = *(void **)D_80016000;
            entry = (u8 *)((*(s32 *)((u8 *)context + 8) << 3) + *(s32 *)((u8 *)context + 0x40));

            if (entry[1] == 0) {
                func_80018ADC(0x5C8);
            }
        }
        return result;
    }
    result = func_80018B5C(0x11FC) != 0;
    return result;
}
