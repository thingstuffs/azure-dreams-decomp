#include "common.h"

extern s16 D_800FE4A6;
extern s32 func_8008FE78(s16 arg0, s16 arg1);
extern s32 func_800C296C(s32 arg0);

/* Update the object's state value according to whether the pair check returns zero. */
void func_800C2A10(void *object) {
    s32 result;

    result = func_8008FE78(D_800FE4A6, *(s16 *)((s8 *)object + 0x16));
    if (result != 0) {
        *(s32 *)((s8 *)object + 0xC) = func_800C296C(0);
    } else {
        *(s32 *)((s8 *)object + 0xC) = func_800C296C(1);
    }
}
