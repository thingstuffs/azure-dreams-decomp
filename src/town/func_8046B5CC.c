#include "common.h"

typedef s32 (*Callback)(s32);

extern s32 func_8001A5D0(void);
extern void *D_80016000[];

s32 func_8001C5CC(void) {
    s32 value;

    if (func_8001A5D0() < 2) goto out;
    value = (*(Callback *)((s8 *)*(void **)((s8 *)D_80016000[0] + 0x20) + 0x2D4))(0);
    if (value == 2) return 1;
out:
    return 0;
}
