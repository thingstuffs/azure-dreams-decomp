#include "common.h"

typedef struct S_80050550_A {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[9];
    /* 0x0C */ s16 unkC;
} S_80050550_A;

typedef struct S_80050550_B {
    /* 0x00 */ u8 pad0[2];
    /* 0x02 */ s16 unk2;
} S_80050550_B;

typedef struct S_80050550_Outer {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ S_80050550_A *fieldA;
    /* 0x08 */ S_80050550_B *fieldB;
} S_80050550_Outer;

/* Writes scaled ratio values with fixed offsets into the two output structs. */
void func_80050550(S_80050550_Outer *outputs, s32 numerator, s32 denominator) {
    register s32 outputValue ASM_REG("v0") = (numerator * 80) / denominator;   /* MATCH pin: slus-diff */
    s32 negativeRatio128 = (-(numerator * 128)) / denominator;
    s32 ratio1024 = (numerator * 1024) / denominator;

    register S_80050550_A *primaryOutput ASM_REG("v1");   /* MATCH pin: slus-diff */

    outputValue = outputValue + 0x30;
    primaryOutput = outputs->fieldA;
    primaryOutput->unk2 = (u8)outputValue;
    primaryOutput->unk1 = (u8)outputValue;
    primaryOutput->unk0 = (u8)outputValue;

    outputValue = 0x180;
    primaryOutput = outputs->fieldA;
    outputValue = outputValue - negativeRatio128;
    primaryOutput->unkC = outputValue;

    outputValue = 0x400;
    outputValue = outputValue - ratio1024;
    outputs->fieldB->unk2 = outputValue;
}
