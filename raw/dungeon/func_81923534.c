#include "common.h"

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))
#define VFIELD(expr, type, offset) (*(volatile type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C();
extern s32 rand(void);
extern void func_8003DB94();

extern u8 D_80024C0C[16];
extern u8 D_80045340[16];
extern u8 D_800DE870[16];

void func_80024D34(void *arg0, void *arg1)
{
    u16 flags;
    void *control;
    void *control2;
    void *position;
    void *node;
    void *sub;
    s32 random;

    node = func_8003FC64(0x212);
    if (node != 0) {
        sub = (u8 *)node + 0x20;
        FIELD(sub, s16, 0x5A) = 0xE;
        FIELD(sub, s16, 0x5C) = 0xE;
        FIELD(node, void *, 0x10) = D_80024C0C;
        func_8004491C(node, D_80045340);

        control = FIELD(node, void *, 0xC);
        FIELD(control, s16, 0x10) = 0x60;
        flags = FIELD(control, u16, 0x14) | 0xC;
        VFIELD(control, u16, 0x14) = flags;
        ASM_KEEP(flags);
        FIELD(control, u16, 0x14) = flags | 2;

        position = FIELD(node, void *, 8);
        random = rand();
        FIELD(position, s16, 2) = FIELD(arg1, u16, 2)
                                  + ((random & 0x1F) - 0x10);
        random = rand();
        FIELD(position, s16, 6) = FIELD(arg1, u16, 6)
                                  + ((random & 0x1F) - 0x10);
        random = rand();
        FIELD(position, s16, 0xA) = FIELD(arg1, u16, 0xA)
                                    + ((random & 0x1F) - 0x10);

        control2 = FIELD(node, void *, 0xC);
        FIELD(control2, s16, 0x1E) = 0xC00;
        FIELD(control2, s16, 0x1C) = 0xC00;
        FIELD(control2, u8, 0xE) = 0x80;
        FIELD(control2, u8, 0xD) = 0x80;
        FIELD(control2, u8, 0xC) = 0x80;
        FIELD(control2, s16, 0x12) = 0x7DCF;
        FIELD(control2, u16, 0x14) = FIELD(control2, u16, 0x14) | 0x100;
        func_8003DB94(control2, D_800DE870, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame, s2/s1/s0 holds, and CFG.
   Unsigned byte fields keep the shared 0x80 store value as +128, matching
   retail's addiu before the three sb operations. */
