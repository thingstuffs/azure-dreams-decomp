#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80016000[0x10];

void func_8001A760(s32 arg0, s32 arg1, s32 arg2) {
    register void *ctx ASM_REG("$7");
    register void *tile ASM_REG("$4");
    register void *out1 ASM_REG("$9");
    register void *out2 ASM_REG("$5");
    register s32 quotient ASM_REG("$3");
    register s32 coord ASM_REG("$2");

    ctx = *(void **)D_80016000;
    ASM_KEEP(ctx);
    tile = (u8 *)*FIELD(ctx, void **, 0x30) + (FIELD(ctx, s32, 8) << 5);
    ASM_KEEP(tile);
    out1 = FIELD(ctx, void *, 0x1C);
    ASM_KEEP(out1);
    quotient = (arg1 << 6) / 10;
    ASM_KEEP(quotient);
    coord = FIELD(tile, s16, 0xC);
    coord += 0x20;
    ASM_KEEP(coord);
    quotient += coord;
    FIELD(out1, s32, 4) = quotient;

    out2 = FIELD(ctx, void *, 0x1C);
    ASM_KEEP(out2);
    quotient = (arg2 << 6) / 10;
    ASM_KEEP(quotient);
    coord = FIELD(tile, s16, 0xE);
    coord += 0x20;
    ASM_KEEP(coord);
    quotient += coord;
    FIELD(out2, s32, 8) = quotient;
}

/* MECHANISM: Frameless leaf with ctx/tile held in $a3/$a0 and split destination
   bases in $t1/$a1. Quotient and coordinate live ranges are pinned to $v1/$v0;
   the split load seams preserve both lh delay nops and leave $t0/$t2 for /10. */
