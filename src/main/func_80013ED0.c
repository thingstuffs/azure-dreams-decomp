#include "common.h"

extern s32 func_8004B4A8(void *arg0);
extern void *func_8003FE78(s32 arg0, void *arg1, s32 arg2);
extern void func_8004491C(void *arg0, void *arg1);
extern void func_80026F58(void *arg0);
extern void func_80026FB4(void *arg0);
extern void bzero(void *arg0, s32 arg1);
extern void func_80026DF0(void *arg0, s32 arg1);
extern s32 func_80026DC8(void *arg0);
extern void func_80026E90(void *arg0, s32 arg1);

extern u8 D_8002B850[];
extern u8 D_80027DD0[];
extern u8 D_80026AE4[];

void *func_80026ED0(s32 arg0, s32 arg1)
{
    void *base;
    void *temp_s1;

    base = D_8002B850;
    temp_s1 = (u8 *)base + 0x20;
    if (func_8004B4A8(base) == 0) {
        base = func_8003FE78(0, base, 0x45);
        ASM_KEEP(base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8004491C(base, D_80027DD0);
        func_80026F58(temp_s1);
        return;
    }
    func_80026FB4(base);
    *(u16 *)((u8 *)base + 0x1E) &= 0x7FFF;
    bzero(temp_s1, 0xF0);
    func_80026DF0(temp_s1, 4);
    {
        register void *body ASM_REG("$17") = temp_s1;   /* MATCH pin: retail keeps a computation the compiler would drop */

        ASM_KEEP(body);   /* MATCH pin: load-bearing for the whole function shape */
        *(void **)((u8 *)base + 0xC) = (u8 *)body + 0x50;
        *(s32 *)((u8 *)body + 0x5C) = func_80026DC8((u8 *)body + 0x60);
        *(s32 *)((u8 *)body + 0x24) = arg1;
        func_80026E90(body, arg0);
    }
    *(void **)((u8 *)base + 0x10) = D_80026AE4;
    return base;
}
