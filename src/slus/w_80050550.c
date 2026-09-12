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

/* Sets equal RGB components and two scaled fields from the supplied ratio. */
void func_80050550(S_80050550_Outer *outputs, s32 numerator, s32 denominator) {
    s32 output_value = (numerator * 80) / denominator;
    s32 negative_ratio_128 = (-(numerator * 128)) / denominator;
    s32 ratio_1024 = (numerator * 1024) / denominator;

    S_80050550_A *primary_output;

    output_value = output_value + 0x30;
    primary_output = outputs->fieldA;
    primary_output->unk2 = (u8)output_value;
    primary_output->unk1 = (u8)output_value;
    primary_output->unk0 = (u8)output_value;

    output_value = 0x180 - negative_ratio_128;
    outputs->fieldA->unkC = output_value;

    output_value = 0x400 - ratio_1024;
    outputs->fieldB->unk2 = output_value;
}
