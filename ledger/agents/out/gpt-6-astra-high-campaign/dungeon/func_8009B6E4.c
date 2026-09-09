#include "common.h"

extern s32 func_800A6D30(s32, s32, s32, s32);
extern s16 D_80083466[];

/* Stores the low four bits of the computed result in the global slot. */
void func_800A0E44(s32 first_input, s32 second_input, s32 third_input, s32 fourth_input) {
    D_80083466[0] = func_800A6D30(first_input, second_input, third_input, fourth_input) & 0xF;
}
