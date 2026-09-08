#include "common.h"

extern void func_800A9A0C(void *);
extern void func_800AA258(void);
extern void func_800AA6B4(s32, s32, s32, s32);
extern void func_800AAA54(s32, s32, s32, s32);
extern u16 D_80083462;
extern void *D_80083470;

void func_800D4494(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    void *call_a0;
    s8 temp_s0;
    s32 pre_s0;
    s32 wide_s0;

    if (!(D_80083462 & 0x2000)) {
        if (*(s32 *)(arg3 + 0x1C) & 0x100) {
            func_800AA258();
            return;
        }
        if (*(u8 *)(arg0 + 0x9A) != 0xE) {
            *(u8 *)(arg0 + 0x9A) = 0xE;
        }
    }
    if (*(s8 *)(arg3 + 0x6D) > 0) {
        call_a0 = arg3;
        ASM_KEEP(call_a0);   /* MATCH pin: keeps a statement from moving across a call/branch */
        temp_s0 = *(volatile s8 *)(arg3 + 0x6D);
        *(s32 *)(arg3 + 0x60) = 0;
        pre_s0 = (u8)temp_s0 << 0x18;
        ASM_KEEP(pre_s0);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_800A9A0C(call_a0);
        wide_s0 = ((s32)pre_s0 >> 0x18) << 0x10;
        if ((wide_s0 != 0) && (*(s8 *)(arg3 + 0x6D) == 0)) {
            *(u8 *)(arg3 + 0x28) -= 1;
        }
        if (*(u8 *)(arg3 + 0x28) == 0) {
            D_80083470 = arg3 - 0x20;
            func_800AAA54(arg0, arg1, arg2, 0);
            return;
        }
    }
    if (*(s16 *)(arg3 + 0x64) != 0) {
        func_800AA6B4(arg0, arg1, arg2, 0);
    }
}
