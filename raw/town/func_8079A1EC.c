#include "common.h"

extern void *D_80016000;
extern s32 D_8001601C;
extern s32 D_80016084;
extern void *D_80017508;

void func_8079A1EC(void)
{
    void *state = D_80016000;
    register void *callback_base ASM_REG("$3");

    *(void **)(*(void **)((u8 *)state + 0x1C) + 0x40) = &D_8001601C;
    callback_base = *(void **)((u8 *)state + 0x20);
    D_80017508 = &D_80016084;
    (*(void (**)(s32, void *))((u8 *)callback_base + 0x28C))(2, state);
}
