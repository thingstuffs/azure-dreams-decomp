#include "common.h"

extern u32 func_800352FC(void);
extern void func_800A4F84(void);

/* Set the object callback when func_800352FC returns nonzero. */
void func_800A4F4C(void *object, s32 value_1, s32 value_2, s32 value_3) {
    if (func_800352FC() != 0) {
        *(void **)((u8 *)object + 0x24) = func_800A4F84;
    }
}
