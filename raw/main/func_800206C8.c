#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_804007A4[];
extern u8 D_804007CC[];
extern u8 D_80407298[];
extern u8 D_8040861C[];
extern u8 D_8040C318[];
extern u16 D_8040C336;
__asm__(".set D_8040C336, 0x8040C336");

extern s32 func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_80040560(s32 arg0, void *arg1);
extern s32 func_80047FD8(void *arg0);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_804075A8(s32 arg0);
extern s32 func_804075D0(void *arg0, s32 arg1);
extern u32 func_80407688(void *arg0, s32 arg1);
extern void func_8040777C(void *arg0);
extern void func_804077D4(void *arg0);

void func_800206C8(s32 arg0)
{
    void *base;
    void *base_use;
    void *sub;
    void *work;

    base = D_8040C318;
    sub = D_8040C318 + 0x20;
    if (func_80047FD8(base) == 0) {
        work = (void *)(unsigned long)func_8003C714(0, base, 0x42);
        if (work == 0) {
            func_8007C040(D_804007A4, D_804007CC, 0x136);
            func_8007BEF0(1);
        }
        func_80040560((s32)(unsigned long)work, D_8040861C);
        func_8040777C(sub);
        return;
    }
    func_804077D4(base);
    D_8040C336 &= 0x7FFF;
    func_8007BFE0(sub, 0xE4);
    if (func_804075D0(sub, 4)) {
        base_use = base;
    } else {
        base_use = (u8 *)sub - 0x20;
    }
    FIELD(base_use, s32, 0xC) = (s32)(unsigned long)((u8 *)sub + 0x50);
    FIELD(sub, s32, 0x5C) = func_804075A8(FIELD(sub, s32, 0x60));
    func_80407688(sub, arg0);
    {
        register void *final_base ASM_REG("$2");

        final_base = base_use;
        ASM_KEEP(final_base);
        FIELD(final_base, s32, 0x10) =
            (s32)(unsigned long)D_80407298;
    }
}
