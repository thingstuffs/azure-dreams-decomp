#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x18];
    u8 unk18;
    u8 pad19[2];
    u8 unk1B;
} S_800561D8_D80086A40;

typedef struct {
    u8 pad00[8];
    s16 unk8;
    s16 unkA;
} S_800561D8_D80086C00;

typedef struct {
    u16 f0;
    s16 pad[7];
} S_800561D8_D80073738;

typedef struct {
    u8 pad00[0x10];
    u16 unk10;
    u16 unk12;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    s16 unk18;
    u8 pad1A[2];
    u8 unk1C;
} S_800561D8_Arg0;

typedef struct {
    u8 pad00[4];
    s32 unk4;
    u8 pad08[4];
    s32 unkC;
    u8 pad10[4];
    s32 unk14;
    u8 pad18[0x14];
    s32 unk2C;
} S_800561D8_Arg1;

extern S_800561D8_D80086A40 D_80086A40[16];
extern S_800561D8_D80086C00 D_80086C00[8];
extern s16 D_80086D50[8];
extern u8 D_8007382A[16];
extern S_800561D8_D80073738 D_80073738;

void func_800561D8(S_800561D8_Arg0 *arg0, S_800561D8_Arg1 *arg1)
{
    S_800561D8_Arg0 *t0 = arg0;
    S_800561D8_D80086A40 *baseA = D_80086A40;
    S_800561D8_D80086A40 *entryA;
    register s32 a0 ASM_REG("$4");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 prod;
    s32 a2;
    s32 a3;
    s32 scale;
    s32 sum;

    a0 = D_80086D50[0];
    entryA = &baseA[a0];
    sum = entryA->unk1B + t0->unk16;
    ASM_KEEP(sum);   /* MATCH pin: slus-diff */
    sum += t0->unk17;
    a0 = arg1->unk4;
    sum += a0;
    a0 = sum - 0xC0;
    if (D_8007382A[0] != 0) {
        a0 = 0x40;
    }
    if (a0 < 0) {
        a0 = 0;
    }
    if (a0 >= 0x80) {
        a0 = 0x7F;
    }
    t0->unk18 = a0;

    prod = entryA->unk18 * D_80073738.f0;
    prod *= arg1->unk14;
    prod *= arg1->unkC;
    prod = (u32)prod >> 0xE;
    prod *= t0->unk14;
    scale = prod * t0->unk15;
    {
        register s32 shifted ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        shifted = scale >> 0xE;
        a2 = shifted;
        if (a0 >= 0x40) {
            a3 = shifted;
            prod = a0 & 0x3F;
            scale = 0x40 - prod;
            prod = a3 * 2;
            a2 = (scale * prod) >> 7;
        } else {
            s32 doubled;
            doubled = a2 * 2;
            a3 = (a0 * doubled) >> 7;
        }
    }

    {
        S_800561D8_D80086C00 *baseC = D_80086C00;
        S_800561D8_D80086C00 *entryC;
        a0 = D_80086D50[0];
        entryC = &baseC[a0];
        prod = a2 * entryC->unk8;
        scale = entryC->unkA;
        a0 = a3 * scale;
        a2 = prod >> 7;
        a3 = a0 >> 7;
        t0->unk10 = (u16)((a2 * (t0->unk1C & 0x7F)) >> 7);
        t0->unk12 = (u16)((a3 * (t0->unk1C & 0x7F)) >> 7);
    }

    if (((u32)arg1->unk2C) >= 0x40) {
        t0->unk10 = (u16)((t0->unk10 * t0->unk10) >> 14);
        t0->unk12 = (u16)((t0->unk12 * t0->unk12) >> 14);
    }
}
