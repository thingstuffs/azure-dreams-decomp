#include "common.h"

extern u8 D_80080A8A[12];
extern u32 D_80081494[3];
extern u8 D_800814AC[12];
extern u8 D_800814A4[12];

void func_800439F8(void)
{
    if (D_80080A8A[0] != 0) {
        u8 *page;
        register u32 value0 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        u8 value4;
        register u8 value6 ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        page = (u8 *)0x80010000;
        value0 = D_80081494[0];
        value4 = D_800814AC[0];
        value6 = D_800814A4[0];
        D_80080A8A[0] = 0;
        *(u32 *)(page + 0x3180) = value0;
        *(u8 *)(page + 0x3184) = value4;
        *(u8 *)(page + 0x3186) = value6;
    } else {
        u8 *page;
        u32 value0;
        u8 value4;
        u8 value6;
        page = (u8 *)0x80010000;
        value0 = *(u32 *)(page + 0x3180);
        value4 = *(u8 *)(page + 0x3184);
        value6 = *(u8 *)(page + 0x3186);
        D_80081494[0] = value0;
        D_800814AC[0] = value4;
        D_800814A4[0] = value6;
    }
}
