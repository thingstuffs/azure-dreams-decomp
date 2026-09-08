#include "common.h"

extern u8 D_80016000[0x10];

typedef s32 (*FuncT)(s32);

/* Invoke the callback with 1 and check whether the stored value is at least 728. */
s32 func_8067F564(void) {
    (*(FuncT *)((u8 *)*(void **)((u8 *)*(void **)D_80016000 + 0x20) + 0x258))(1);
    return *(s32 *)((u8 *)*(void **)((u8 *)*(void **)D_80016000 + 0x1C) + 8) >= 0x2D8;
}
