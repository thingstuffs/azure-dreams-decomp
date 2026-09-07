#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_8003DB94();
extern s8 func_8009FB34();
extern void func_800A2B04();
extern s16 func_800BCB04();
extern void func_80099FDC();
extern void func_8009A21C();

extern u8 D_80045340;
extern s32 D_80083498;
extern u8 D_800D4158;
extern u8 D_800D4494;
extern u8 D_800DEEC0;

void *func_800D3F74(s16 arg0, u8 arg1, u8 arg2, s16 arg3)
{
    register s8 *part0 ASM_REG("$17");
    register s8 *result ASM_REG("$18") = NULL;
    register s8 *object ASM_REG("$19");
    register u8 held_arg2 ASM_REG("$20") = arg2;
    register u8 held_arg1 ASM_REG("$21") = arg1;
    s8 *part1;
    s16 height;
    s32 mode;
    u8 x;
    u8 y;

    object = func_8003FD64(0x112, &D_80083498);
    if (object != NULL) {
        result = object + 0x20;
        FIELD(result, s8, 0x13) = 0x34;
        if (arg0 == 1) {
            FIELD(result, s32, 0x14) |= 0x2000;
            FIELD(result, s32, 0x1C) |= 0x2000;
        }
        func_8004491C(object, &D_80045340);
        part0 = FIELD(object, s8 *, 8);
        FIELD(part0, s16, 0xA) = arg3;
        part1 = FIELD(object, s8 *, 0xC);
        FIELD(part1, u8, 0xE) = 0x80;
        FIELD(part1, u8, 0xD) = 0x80;
        FIELD(part1, u8, 0xC) = 0x80;
        FIELD(part1, s16, 0x1E) = 0x1000;
        FIELD(part1, s16, 0x1C) = 0x1000;
        FIELD(part1, u8, 0x24) = held_arg1;
        FIELD(part1, u8, 0x25) = held_arg2;
        FIELD(part1, s16, 0x12) = 0x7E40;
        FIELD(part1, u16, 0x14) |= 0x100;
        func_8003DB94(part1, &D_800DEEC0, 0);
        FIELD(object, void *, 0x10) = &D_800D4158;
        FIELD(result, void *, 0x8C) = &D_800D4494;
        FIELD(part1, s8, 0x26) =
            func_8009FB34(FIELD(part1, u8, 0x24), FIELD(part1, u8, 0x25));
        func_800A2B04(part0, FIELD(part1, u8, 0x24),
                     FIELD(part1, u8, 0x25));
        height = func_800BCB04(FIELD(part0, u16, 2),
                               FIELD(part0, u16, 6),
                               FIELD(part0, s16, 0xA));
        ASM_KEEP_NV(part0);
        FIELD(result, s16, 0x88) = height;
        FIELD(result, s32, 0x90) = 0;
        FIELD(result, s16, 0x92) = arg3 - height;
        FIELD(part1, s32, 0xC) = 0x2C808080;
        FIELD(part1, u16, 0x14) |= 0x8000;
        func_80099FDC(object);
        x = FIELD(part1, u8, 0x24);
        y = FIELD(part1, u8, 0x25);
        mode = 0x3000;
        if (FIELD(result, s32, 0x1C) & 0x2000) {
            mode = 0x300;
        }
        func_8009A21C(x, y, mode);
        FIELD(result, s8, 0x9A) = 0xE;
        FIELD(result, s8, 0x9C) = -1;
        FIELD(result, s32, 0x1C) |= 0x40000200;
        ASM_KEEP_NV(held_arg1);
        ASM_KEEP_NV(held_arg2);
        ASM_KEEP_NV(object);
    }
    ASM_KEEP_NV(result);
    return result;
}

/* MECHANISM: The true-space function uses a 0x30 frame and fixed s1-s5 object/part/argument roles;
   arg0 and arg3 remain naturally allocated so their temporary computations stay in v0.
   Naming x/y before the mode test hoists both lbu operations and removes the one-word load-delay nop;
   the retail store-slot lineage requires 2.7.2-cdk-G0. */
