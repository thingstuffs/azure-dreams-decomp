#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))
#define NORETURN

typedef struct {
    s32 word[6];
} Copy24;

extern void *func_8003FC64();
extern void func_8003DB94();
extern s32 rand();
extern void func_8004491C();
extern void func_80024F24() __attribute__((noreturn));

extern u8 D_80024BB0[];
extern s32 D_80045340;
extern u8 D_800DDC40[];
extern u8 D_800DEC70[];

void *func_818BD52C(void *arg0, void *arg1, s32 arg2, s32 arg3)
{
    s32 color;
    s32 quarter;
    s32 half;
    s32 angle;
    s32 phase;
    s16 bit;
    s16 half16;
    void *part;
    void *base;
    void *coords;
    void *node;
    s32 val;
    register void *ret ASM_REG("$2");

    node = func_8003FC64(0x212);
    if (node != 0) {
        FIELD(node, void *, 0x10) = D_80024BB0;
        base = (u8 *)node + 0x20;
        FIELD(node, s32, 0x20) = FIELD(arg0, s32, 0);
        FIELD(base, s16, 4) = 0;
        FIELD(base, s16, 6) = 0x10;

        color = D_800DDC40[FIELD(FIELD(arg0, void *, 0x18), u8, 0x13)] * 3;
        if (color < 0) {
            color += 3;
        }
        phase = (s16)(arg2 + 1);
        quarter = color >> 2;
        FIELD(base, s16, 0xA) = quarter;
        FIELD(base, s16, 8) = quarter;
        FIELD(base, s16, 0xC) = arg3;

        part = FIELD(node, void *, 0xC);
        FIELD(part, s8, 0xC) = (phase / 4) * 0x80;
        half = phase / 2;
        half16 = half;
        bit = half16 % 2;
        FIELD(part, s8, 0xD) = bit * 0x80;
        bit = phase - (half * 2);
        FIELD(part, s8, 0xE) = bit * 0x80;
        FIELD(part, s16, 0x12) = 0x7DCF;
        FIELD(part, u16, 0x14) |= 0xC;
        FIELD(part, u16, 0x10) |= 0x20;
        FIELD(part, u16, 0x14) |= 0x100;
        func_8003DB94(part, D_800DEC70, 0, phase);

        angle = rand();
        FIELD(part, s16, 0x1A) = angle % 0x1000;
        FIELD(part, s16, 0x1E) = 0xC00;
        FIELD(part, s16, 0x1C) = 0xC00;
        func_8004491C(node, &D_80045340);

        coords = FIELD(node, void *, 8);
        *(Copy24 *)coords = *(Copy24 *)arg1;
        FIELD(coords, s32, 0xC) = FIELD(coords, s32, 0);
        FIELD(coords, s32, 0x10) = FIELD(coords, s32, 4);
        FIELD(coords, s32, 0x14) = FIELD(coords, s32, 8);
        ret = node;
        val = FIELD(coords, s32, 0x14) + ((u32)FIELD(base, s16, 0xA) << 16);
        ASM_USE(ret);
        FIELD(coords, s32, 0x14) = val;
        func_80024F24(coords, val);
    }
    return node;
}
