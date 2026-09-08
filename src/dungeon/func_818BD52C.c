#include "common.h"

typedef struct S_818BD52C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BD52C_0;   /* node in func_818BD52C */

typedef struct S_818BD52C_1 {
    s32 unk_00;
    u8 pad_04[0x14];
    void * unk_18;
} S_818BD52C_1;   /* arg0 in func_818BD52C */

typedef struct S_818BD52C_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
} S_818BD52C_2;   /* base in func_818BD52C */

typedef struct S_818BD52C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BD52C_3;   /* part in func_818BD52C */

typedef struct S_818BD52C_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818BD52C_4;   /* coords in func_818BD52C */

typedef struct S_818BD52C_5 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_818BD52C_5;   /* ((S_818BD52C_1 *)arg0)->unk_18 in func_818BD52C */


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

void *func_818BD52C(S_818BD52C_1 *arg0, void *arg1, s32 arg2, s32 arg3)
{
    s32 color;
    s32 quarter;
    s32 half;
    s32 angle;
    s32 phase;
    s16 bit;
    s16 half16;
    S_818BD52C_3 *part;
    S_818BD52C_2 *base;
    S_818BD52C_4 *coords;
    void *node;
    s32 val;
    register void *ret ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    node = func_8003FC64(0x212);
    if (node != 0) {
        ((S_818BD52C_0 *)node)->unk_10 = D_80024BB0;
        base = (u8 *)node + 0x20;
        ((S_818BD52C_0 *)node)->unk_20 = arg0->unk_00;
        base->unk_04 = 0;
        base->unk_06 = 0x10;

        color = D_800DDC40[((S_818BD52C_5 *)(arg0->unk_18))->unk_13] * 3;
        if (color < 0) {
            color += 3;
        }
        phase = (s16)(arg2 + 1);
        quarter = color >> 2;
        base->unk_0A = quarter;
        base->unk_08 = quarter;
        base->unk_0C = arg3;

        part = ((S_818BD52C_0 *)node)->unk_0C;
        part->unk_0C = (phase / 4) * 0x80;
        half = phase / 2;
        half16 = half;
        bit = half16 % 2;
        part->unk_0D = bit * 0x80;
        bit = phase - (half * 2);
        part->unk_0E = bit * 0x80;
        part->unk_12 = 0x7DCF;
        part->unk_14 |= 0xC;
        part->unk_10 |= 0x20;
        part->unk_14 |= 0x100;
        func_8003DB94(part, D_800DEC70, 0, phase);

        angle = rand();
        part->unk_1A = angle % 0x1000;
        part->unk_1E = 0xC00;
        part->unk_1C = 0xC00;
        func_8004491C(node, &D_80045340);

        coords = ((S_818BD52C_0 *)node)->unk_08;
        *(Copy24 *)coords = *(Copy24 *)arg1;
        coords->unk_0C = coords->unk_00;
        coords->unk_10 = coords->unk_04;
        coords->unk_14 = coords->unk_08;
        ret = node;
        val = coords->unk_14 + ((u32)base->unk_0A << 16);
        ASM_USE(ret);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        coords->unk_14 = val;
        func_80024F24(coords, val);
    }
    return node;
}
