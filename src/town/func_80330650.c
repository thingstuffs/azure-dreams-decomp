#include "common.h"

typedef void (*Callback)(s32);

extern s8 D_80016000[];

void func_8001AE50(void) {
    ((Callback) *(void **)
        ((u8 *) *(void **)((u8 *) *(void **)D_80016000 + 0x20) + 0x280))(0xC1);
}
