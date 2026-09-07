#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    s16 x;
    u16 y;
} LocalPoint;

extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();
extern s16 rand();

extern LocalPoints D_80024004;
extern u8 D_80024874[];
extern s32 D_80045340;
extern u8 D_80083780[];
extern u8 D_800DECF8[];

void func_8196B780(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4,
                   s32 arg5)
{
    LocalPoints points;
    void *node;
    void *sub;
    void *part;
    void *coords;
    u8 *coord_base;
    LocalPoint *point_base;
    LocalPoint *point;
    s32 point_index;
    register s32 x_arg3 ASM_REG("$21") = arg3;
    register s32 x_arg4 ASM_REG("$19") = arg4;
    register s32 x_arg5 ASM_REG("$20") = arg5;

    points = D_80024004;
    point_base = (LocalPoint *)&points;
    node = func_8003FC64(0x212);
    if (node != 0) {
        sub = (u8 *)node + 0x20;
        FIELD(sub, s16, 0x2C) = 0x4;
        FIELD(node, void *, 0x10) = D_80024874;
        func_8004491C(node, &D_80045340);

        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x10) = 0x20;
        FIELD(part, u16, 0x14) |= 0xC;
        FIELD(part, s16, 0x1A) = (rand() & 7) << 9;
        FIELD(part, s16, 6) = 0;

        coords = FIELD(node, void *, 8);
        coord_base = D_80083780;
        FIELD(coords, s16, 2) = x_arg3;
        FIELD(coords, s16, 6) = x_arg4;
        FIELD(coords, s16, 0xA) = x_arg5;
        FIELD(coords, s16, 2) += FIELD(coord_base, u16, 2);
        FIELD(coords, s16, 6) += FIELD(coord_base, u16, 6);
        FIELD(coords, s16, 0xA) += FIELD(coord_base, u16, 0xA);

        FIELD(coords, s16, 2) += (rand() & 0x3F) - 0x20;
        FIELD(coords, s16, 6) += (rand() & 0x3F) - 0x20;
        FIELD(coords, s16, 0xA) += (rand() & 0x3F) - 0x40;

        FIELD(sub, s32, 0x94) = -0x60000;
        FIELD(sub, s32, 0xA0) = 0x20000;
        point = point_base;
        point_index = FIELD(arg0, s16, 0x26);
        point += point_index;
        FIELD(sub, s32, 0x8C) = point->x << 18;
        point = point_base;
        point_index = FIELD(arg0, s16, 0x26);
        point += point_index;
        FIELD(sub, s32, 0x90) = point->y << 18;

        FIELD(sub, s32, 0x8C) +=
            -0x80000 + ((rand() & 0x3FFF) << 6);
        FIELD(sub, s32, 0x90) +=
            -0x80000 + ((rand() & 0x3FFF) << 6);
        FIELD(sub, s32, 0x94) +=
            -0x80000 + ((rand() & 0x3FFF) << 6);

        part = FIELD(node, void *, 0xC);
        FIELD(part, s16, 0x1C) = FIELD(part, s16, 0x1E) = 0x1000;
        FIELD(part, u8, 0xC) = FIELD(part, u8, 0xD) =
            FIELD(part, u8, 0xE) = 0x80;
        FIELD(part, s16, 0x12) = 0x7DCE;
        FIELD(part, u16, 0x14) |= 0x100;
        func_8003DB94(part, D_800DECF8, 0);
    }
    ASM_KEEP(x_arg3);
    ASM_KEEP(x_arg4);
    ASM_KEEP(x_arg5);
}

/* MECHANISM: The 0x20 byte-aligned copy object preserves the 0x58 frame and lwl/lwr stack copy;
   a held D_80083780 base plus RMW updates restores the load-delay moves and $a0 base.
   Epilogue-held arg pins and split point base/index/add produce the retail saved roles and $s6+$v0 order. */
