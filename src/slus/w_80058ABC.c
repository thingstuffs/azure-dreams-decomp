#include "common.h"

extern s32 func_800589B8(s32 a0);
extern u32 func_80058A7C(s32 a0, s32 a1, s32 a2, s32 a3);

/* Packs the low bytes of four successive func_800589B8 results into a word. */
u32 func_80058ABC(s32 input)
{
    s32 first_byte, second_byte, third_byte, fourth_byte;

    first_byte = func_800589B8(input);
    second_byte = func_800589B8(input);
    third_byte = func_800589B8(input);
    fourth_byte = func_800589B8(input);
    return func_80058A7C(first_byte & 0xFF, second_byte & 0xFF, third_byte & 0xFF, fourth_byte & 0xFF);
}
