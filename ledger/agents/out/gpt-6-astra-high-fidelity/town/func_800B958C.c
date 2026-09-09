#include "common.h"

extern s32 func_80042900(void *, s8);
extern s32 func_800B5E10(s32);
extern s32 func_80049E88(void *);

s32 func_800B6CEC(void *arg0) {
    s32 temp = *((u8 *) arg0 + 0x13);

    if (temp != 0) {
        if ((func_80042900(arg0, 10) << 0x10) != 0) {
            temp = 47;
        } else {
            temp = func_800B5E10(temp);
        }
        ASM_KEEP(temp);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        return temp;
    }
    return func_80049E88(arg0);
}
