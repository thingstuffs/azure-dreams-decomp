#include "common.h"

typedef struct S_80024A64_0 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s16 unk_0C;
    s16 unk_0E;
} S_80024A64_0;   /* arg0 in func_80024A64 */

typedef struct S_80024A64_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024A64_1;   /* arg1 in func_80024A64 */

typedef struct S_80024A64_2 {
    u8 pad_00[0x30];
    s32 unk_30;
    s32 unk_34;
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
    s32 unk_54;
    s32 unk_58;
    u8 pad_5C[0x4];
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
} S_80024A64_2;   /* sc in func_80024A64 */



extern s32 func_80069EF8(void);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80024790(s32, s32);

s32 func_80024A64(S_80024A64_0 *arg0, S_80024A64_1 *arg1, s32 arg2) {
    u8 *sc;
    s32 v30;
    s32 v34;
    s32 v60;
    s32 v64;
    u16 hA;
    u16 hB;
    s16 nA;
    s16 nB;
    s32 i;
    s32 q;
    s32 p;
    register s32 o ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 o2;
    s32 w;
    s32 eA;

    sc = (u8 *)0x1F800000;
    if (arg0->unk_06 < 8) {
        w = arg1->unk_08 - (arg0->unk_06 * 0x180000);
        ((S_80024A64_2 *)sc)->unk_48 = w;
        ((S_80024A64_2 *)sc)->unk_38 = w;
        {
            s32 base = arg0->unk_06;
            register s32 product2 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
            s32 product6;
            product2 = base * 2;
            product6 = (product2 + base) * 2;
            ASM_USE(product2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
            hB = product2;
            hA = product6;
        }
        nB = arg0->unk_06 / 2;
        nA = nB + 1;
    } else if (arg0->unk_06 < 40) {
        {
            s32 constant_w = arg1->unk_08 - (8 * 0x180000);
            ((S_80024A64_2 *)sc)->unk_48 = constant_w;
            ((S_80024A64_2 *)sc)->unk_38 = constant_w;
        }
        hA = 8 * 6;
        hB = 8 * 2;
        nB = 8 / 2;
        nA = nB + 1;
    } else if (arg0->unk_06 < 48) {
        w = arg1->unk_08 - ((48 - arg0->unk_06) * 0x180000);
        ((S_80024A64_2 *)sc)->unk_48 = w;
        ((S_80024A64_2 *)sc)->unk_38 = w;
        {
            s32 base = 48 - arg0->unk_06;
            s32 product2;
            register s32 product6 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            product2 = base * 2;
            product6 = (product2 + base) * 2;
            hB = product2;
            nB = (47 - arg0->unk_06) / 2;
            hA = product6;
            nA = nB + 1;
        }
    } else {
        nA = 0;
        nB = 0;
        hB = 0;
        hA = 0;
    }

    i = 0;
    eA = (s16)nA;
    ((S_80024A64_2 *)sc)->unk_58 = ((S_80024A64_2 *)sc)->unk_68 = arg1->unk_08;
    do {
        q = i * 512;
        o = func_80069EF8() % eA;
        {
            s32 wave_x = func_800644B8(arg0->unk_0C + q);
            o = (s16)o;
            p = (s16)hA + o;
            ((S_80024A64_2 *)sc)->unk_40 = arg1->unk_00 +
                (((wave_x >> 4) * p) << 8);
        }
        ((S_80024A64_2 *)sc)->unk_44 = arg1->unk_04 +
            (((func_80064584(arg0->unk_0C + q) >> 4) * p) << 8);
        {
            s32 wave_x2 = func_800644B8(arg0->unk_0C + q);
            o2 = (s16)hB + o;
            ((S_80024A64_2 *)sc)->unk_50 = arg1->unk_00 +
                (((wave_x2 >> 4) * o2) << 8);
        }
        ((S_80024A64_2 *)sc)->unk_54 = arg1->unk_04 +
            (((func_80064584(arg0->unk_0C + q) >> 4) * o2) << 8);
        p = i + 1;
        o = p * 512;
        ((S_80024A64_2 *)sc)->unk_30 = ((S_80024A64_2 *)sc)->unk_60 = arg1->unk_00 +
            (((func_800644B8(arg0->unk_0C + o) >> 4) * (s16)nB) << 8);
        ((S_80024A64_2 *)sc)->unk_34 = ((S_80024A64_2 *)sc)->unk_64 = arg1->unk_04 +
            (((func_80064584(arg0->unk_0C + o) >> 4) * (s16)nB) << 8);
        func_80024790((s16)i, arg2);
        i = p;
    } while (i < 8);

    i = 0;
    {
        s32 random_raw = func_80069EF8();
        s32 magic = 0x66666667;
        ASM_USE_NV(magic);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        o = random_raw;
        o = o - (o / 5) * 5;
    }
    {
        s32 wave_x;
        s32 shifted_wave_x;
        s32 next30;
        wave_x = func_800644B8(arg0->unk_0E);
        shifted_wave_x = wave_x >> 4;
        ASM_KEEP_DEP_NV(o, shifted_wave_x);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        o = (s16)o;
        o = (s16)hA + o;
        next30 = arg1->unk_00 +
            ((shifted_wave_x * o) << 8);
        ((S_80024A64_2 *)sc)->unk_30 = next30;
        v30 = next30;
    }
    {
        s32 next34;
        next34 = arg1->unk_04 +
            (((func_80064584(arg0->unk_0E) >> 4) * o) << 8);
        ((S_80024A64_2 *)sc)->unk_34 = next34;
        v34 = next34;
    }
    {
        s32 wave_x2 = func_800644B8(arg0->unk_0E + 512);
        s32 next60;
        next60 = arg1->unk_00 +
            (((wave_x2 >> 4) * (s16)hB) << 8);
        ((S_80024A64_2 *)sc)->unk_60 = next60;
        v60 = next60;
    }
    {
        s32 final64 = arg1->unk_04 +
            (((func_80064584(arg0->unk_0E + 512) >> 4) * (s16)hB) << 8);
        ASM_KEEP_NV(final64);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        v64 = final64;
        ((S_80024A64_2 *)sc)->unk_64 = v64;
    }
    q = 512;
    do {
        ((S_80024A64_2 *)sc)->unk_40 = ((S_80024A64_2 *)sc)->unk_30;
        ((S_80024A64_2 *)sc)->unk_44 = ((S_80024A64_2 *)sc)->unk_34;
        ((S_80024A64_2 *)sc)->unk_50 = ((S_80024A64_2 *)sc)->unk_60;
        ((S_80024A64_2 *)sc)->unk_54 = ((S_80024A64_2 *)sc)->unk_64;
        if (i == 7) {
            ((S_80024A64_2 *)sc)->unk_30 = v30;
            ((S_80024A64_2 *)sc)->unk_34 = v34;
            ((S_80024A64_2 *)sc)->unk_60 = v60;
            ((S_80024A64_2 *)sc)->unk_64 = v64;
        } else {
            {
                s32 random_raw = func_80069EF8();
                s32 magic2 = 0x66666667;
                union {
                    long long full;
                    struct { s32 hi; u32 lo; } half;
                } product2;
                s32 quotient2;
                o = random_raw;
                product2.full = (long long)o * magic2;
                quotient2 = (product2.half.hi >> 1) - (o >> 31);
                o = o - quotient2 * 5;
            }
            {
                s32 wave_x3 = func_800644B8(arg0->unk_0E + (i * 512));
                s32 shifted_x3 = wave_x3 >> 4;
                ASM_KEEP_DEP_NV(o, shifted_x3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                o = (s16)o;
                o = (s16)hA + o;
                ((S_80024A64_2 *)sc)->unk_30 = arg1->unk_00 +
                    ((shifted_x3 * o) << 8);
            }
            ((S_80024A64_2 *)sc)->unk_34 = arg1->unk_04 +
                (((func_80064584(arg0->unk_0E + (i * 512)) >> 4) * o) << 8);
            ((S_80024A64_2 *)sc)->unk_60 = arg1->unk_00 +
                (((func_800644B8(arg0->unk_0E + q) >> 4) * (s16)hB) << 8);
            ((S_80024A64_2 *)sc)->unk_64 = arg1->unk_04 +
                (((func_80064584(arg0->unk_0E + q) >> 4) * (s16)hB) << 8);
        }
        func_80024790((s16)i, arg2);
        i = i + 1;
        q = q + 512;
    } while (i < 8);
    return 0;
}
