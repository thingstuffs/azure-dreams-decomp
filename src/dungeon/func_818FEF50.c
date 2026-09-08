#include "common.h"

extern s16 D_80025E80;
extern s32 D_800814A0;

/* Sets the object and global flags and marks the update. */
void func_818FEF50(void *object) {
    u16 *flags = (u16 *)object - 1;

    D_80025E80 = 1;
    *flags |= 0x8000;
    D_800814A0 |= 0x8000;
}
