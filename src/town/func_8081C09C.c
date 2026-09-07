#include "common.h"

extern void func_800478B8();
extern s32 D_800814A0;

void func_8002609C(u8 *arg0, u8 *arg1, u8 *arg2)
{
    s32 amount;
    s32 delta;
    register s32 new_amount ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 position;
    u8 shade;

    amount = *(s32 *)(arg1 + 0x14);
    if (amount != 0) {
        delta = 0x18000;
        new_amount = amount;
        ASM_KEEP(new_amount);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        position = *(s32 *)(arg1 + 8);
        new_amount += delta;
        *(s32 *)(arg1 + 0x14) = new_amount;
        position += amount;
        *(s32 *)(arg1 + 8) = position;

        shade = arg2[0xE] - 0x20;
        arg2[0xE] = shade;
        arg2[0xD] = shade;
        arg2[0xC] = shade;
    }

    func_800478B8(arg2, arg1, amount);
    if (*(u16 *)(arg2 + 0x14) & 0x6000) {
        *(u16 *)(arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
