#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80069EF8(void);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80024790(s32, s32);

s32 func_80024A64(void *arg0, void *arg1, s32 arg2) {
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
    register s32 o ASM_REG("$16");
    s32 o2;
    s32 w;
    s32 eA;

    sc = (u8 *)0x1F800000;
    if (FIELD(arg0, s16, 6) < 8) {
        w = FIELD(arg1, s32, 8) - (FIELD(arg0, s16, 6) * 0x180000);
        FIELD(sc, s32, 0x48) = w;
        FIELD(sc, s32, 0x38) = w;
        {
            s32 base = FIELD(arg0, s16, 6);
            register s32 product2 ASM_REG("$5");
            s32 product6;
            product2 = base * 2;
            product6 = (product2 + base) * 2;
            ASM_USE(product2);
            hB = product2;
            hA = product6;
        }
        nB = FIELD(arg0, s16, 6) / 2;
        nA = nB + 1;
    } else if (FIELD(arg0, s16, 6) < 40) {
        {
            s32 constant_w = FIELD(arg1, s32, 8) - (8 * 0x180000);
            FIELD(sc, s32, 0x48) = constant_w;
            FIELD(sc, s32, 0x38) = constant_w;
        }
        hA = 8 * 6;
        hB = 8 * 2;
        nB = 8 / 2;
        nA = nB + 1;
    } else if (FIELD(arg0, s16, 6) < 48) {
        w = FIELD(arg1, s32, 8) - ((48 - FIELD(arg0, s16, 6)) * 0x180000);
        FIELD(sc, s32, 0x48) = w;
        FIELD(sc, s32, 0x38) = w;
        {
            s32 base = 48 - FIELD(arg0, s16, 6);
            s32 product2;
            register s32 product6 ASM_REG("$4");
            product2 = base * 2;
            product6 = (product2 + base) * 2;
            hB = product2;
            nB = (47 - FIELD(arg0, s16, 6)) / 2;
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
    FIELD(sc, s32, 0x58) = FIELD(sc, s32, 0x68) = FIELD(arg1, s32, 8);
    do {
        q = i * 512;
        o = func_80069EF8() % eA;
        {
            s32 wave_x = func_800644B8(FIELD(arg0, s16, 0xC) + q);
            o = (s16)o;
            p = (s16)hA + o;
            FIELD(sc, s32, 0x40) = FIELD(arg1, s32, 0) +
                (((wave_x >> 4) * p) << 8);
        }
        FIELD(sc, s32, 0x44) = FIELD(arg1, s32, 4) +
            (((func_80064584(FIELD(arg0, s16, 0xC) + q) >> 4) * p) << 8);
        {
            s32 wave_x2 = func_800644B8(FIELD(arg0, s16, 0xC) + q);
            o2 = (s16)hB + o;
            FIELD(sc, s32, 0x50) = FIELD(arg1, s32, 0) +
                (((wave_x2 >> 4) * o2) << 8);
        }
        FIELD(sc, s32, 0x54) = FIELD(arg1, s32, 4) +
            (((func_80064584(FIELD(arg0, s16, 0xC) + q) >> 4) * o2) << 8);
        p = i + 1;
        o = p * 512;
        FIELD(sc, s32, 0x30) = FIELD(sc, s32, 0x60) = FIELD(arg1, s32, 0) +
            (((func_800644B8(FIELD(arg0, s16, 0xC) + o) >> 4) * (s16)nB) << 8);
        FIELD(sc, s32, 0x34) = FIELD(sc, s32, 0x64) = FIELD(arg1, s32, 4) +
            (((func_80064584(FIELD(arg0, s16, 0xC) + o) >> 4) * (s16)nB) << 8);
        func_80024790((s16)i, arg2);
        i = p;
    } while (i < 8);

    i = 0;
    {
        s32 random_raw = func_80069EF8();
        s32 magic = 0x66666667;
        ASM_USE_NV(magic);
        ASM_USE_NV(random_raw);
        o = random_raw;
        ASM_KEEP_NV(o);
        o = o - (o / 5) * 5;
    }
    {
        s32 wave_x;
        s32 shifted_wave_x;
        s32 next30;
        wave_x = func_800644B8(FIELD(arg0, s16, 0xE));
        shifted_wave_x = wave_x >> 4;
        ASM_KEEP_DEP_NV(o, shifted_wave_x);
        o = (s16)o;
        o = (s16)hA + o;
        next30 = FIELD(arg1, s32, 0) +
            ((shifted_wave_x * o) << 8);
        FIELD(sc, s32, 0x30) = next30;
        v30 = next30;
    }
    {
        s32 next34;
        next34 = FIELD(arg1, s32, 4) +
            (((func_80064584(FIELD(arg0, s16, 0xE)) >> 4) * o) << 8);
        FIELD(sc, s32, 0x34) = next34;
        v34 = next34;
    }
    {
        s32 wave_x2 = func_800644B8(FIELD(arg0, s16, 0xE) + 512);
        s32 next60;
        next60 = FIELD(arg1, s32, 0) +
            (((wave_x2 >> 4) * (s16)hB) << 8);
        FIELD(sc, s32, 0x60) = next60;
        v60 = next60;
    }
    {
        s32 final64 = FIELD(arg1, s32, 4) +
            (((func_80064584(FIELD(arg0, s16, 0xE) + 512) >> 4) * (s16)hB) << 8);
        ASM_KEEP_NV(final64);
        v64 = final64;
        FIELD(sc, s32, 0x64) = v64;
    }
    q = 512;
    do {
        FIELD(sc, s32, 0x40) = FIELD(sc, s32, 0x30);
        FIELD(sc, s32, 0x44) = FIELD(sc, s32, 0x34);
        FIELD(sc, s32, 0x50) = FIELD(sc, s32, 0x60);
        FIELD(sc, s32, 0x54) = FIELD(sc, s32, 0x64);
        if (i == 7) {
            FIELD(sc, s32, 0x30) = v30;
            FIELD(sc, s32, 0x34) = v34;
            FIELD(sc, s32, 0x60) = v60;
            FIELD(sc, s32, 0x64) = v64;
        } else {
            {
                s32 random_raw = func_80069EF8();
                register s32 magic2 ASM_REG("$3") = 0x66666667;
                union {
                    long long full;
                    struct { s32 hi; u32 lo; } half;
                } product2;
                s32 quotient2;
                ASM_USE_NV(random_raw);
                o = random_raw;
                product2.full = (long long)o * magic2;
                quotient2 = (product2.half.hi >> 1) - (o >> 31);
                o = o - quotient2 * 5;
            }
            {
                s32 wave_x3 = func_800644B8(FIELD(arg0, s16, 0xE) + (i * 512));
                s32 shifted_x3 = wave_x3 >> 4;
                ASM_KEEP_DEP_NV(o, shifted_x3);
                o = (s16)o;
                o = (s16)hA + o;
                FIELD(sc, s32, 0x30) = FIELD(arg1, s32, 0) +
                    ((shifted_x3 * o) << 8);
            }
            FIELD(sc, s32, 0x34) = FIELD(arg1, s32, 4) +
                (((func_80064584(FIELD(arg0, s16, 0xE) + (i * 512)) >> 4) * o) << 8);
            FIELD(sc, s32, 0x60) = FIELD(arg1, s32, 0) +
                (((func_800644B8(FIELD(arg0, s16, 0xE) + q) >> 4) * (s16)hB) << 8);
            FIELD(sc, s32, 0x64) = FIELD(arg1, s32, 4) +
                (((func_80064584(FIELD(arg0, s16, 0xE) + q) >> 4) * (s16)hB) << 8);
        }
        func_80024790((s16)i, arg2);
        i = i + 1;
        q = q + 512;
    } while (i < 8);
    return 0;
}
