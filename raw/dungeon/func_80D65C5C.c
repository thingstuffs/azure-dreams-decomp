#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

typedef s32 M2C_UNK;

extern void *func_8003FC64(s32, s32);
extern s32 rand(void);
extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

extern s32 D_80045340;
extern M2C_UNK D_800DE870;
extern s16 D_800E2468[];
extern u8 D_80171384[];

void func_80D65C5C(void *arg0, s32 arg1)
{
    void *node;
    void *sprite;
    s16 *offsets;

    node = func_8003FC64(0x212, arg1);
    if (node != 0) {
        FIELD(node, void *, 0x10) = D_80171384;

        FIELD(FIELD(node, void *, 8), u16, 2) =
            FIELD(FIELD(arg0, void *, 8), u16, 2);
        FIELD(FIELD(node, void *, 8), u16, 6) =
            FIELD(FIELD(arg0, void *, 8), u16, 6);
        FIELD(FIELD(node, void *, 8), s16, 0xA) =
            FIELD(FIELD(arg0, void *, 8), u16, 0xA) - 0x58;

        offsets = (s16 *)((u8 *)D_800E2468 + (((u32)arg1 >> 7) & 0x1C));
        FIELD(FIELD(node, void *, 8), u16, 2) += offsets[0] * 0x12;
        FIELD(FIELD(node, void *, 8), u16, 6) += offsets[1] * 0x12;

        FIELD(FIELD(node, void *, 0xC), s16, 6) = 6;
        FIELD(FIELD(node, void *, 8), s32, 0xC) =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        FIELD(FIELD(node, void *, 8), s32, 0x10) =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;
        FIELD(FIELD(node, void *, 8), s32, 0x14) =
            ((rand() & 0x7FFF) - 0x4000) * 0x10;

        FIELD(FIELD(node, void *, 8), s32, 0xC) +=
            offsets[0] * 0x1C0000;
        FIELD(FIELD(node, void *, 8), s32, 0x10) +=
            offsets[1] * 0x1C0000;

        sprite = (u8 *)node + 0x20;
        FIELD(sprite, u16, 0xA) = arg1;
        FIELD(sprite, s16, 0xC) = 0xC;
        FIELD(sprite, s16, 0xE) = 0xC;
        func_8004491C(node, &D_80045340);

        {
            void *part = FIELD(node, void *, 0xC);

            FIELD(part, u16, 0x14) |= 0xC;
            FIELD(part, s16, 0x10) = 0x60;
            FIELD(part, u16, 0x14) |= 2;
            FIELD(part, s16, 0x1C) = 0x800;
            FIELD(part, s16, 0x1E) = 0x800;
            FIELD(part, u8, 0xE) = 0x80;
            FIELD(part, u8, 0xD) = 0x80;
            FIELD(part, u8, 0xC) = 0x80;
            FIELD(part, u16, 0x14) |= 0x100;
            FIELD(part, s16, 0x12) = 0x7DCF;
            func_8003DB94(part, &D_800DE870, 0);
        }
    }
}
