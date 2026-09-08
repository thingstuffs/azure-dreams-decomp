#include "common.h"

extern u8 D_80016000[0x10];

typedef s32 (*FuncT)(s32);

/* Calls the state callback with one and checks whether the position value is below 0x501. */
s32 func_80016EC8(void) {
    (*(FuncT *)((u8 *)*(void **)((u8 *)*(void **)D_80016000 + 0x20) + 0x248))(1);
    return *(s32 *)((u8 *)*(void **)((u8 *)*(void **)D_80016000 + 0x1C) + 8) < 0x501;
}
