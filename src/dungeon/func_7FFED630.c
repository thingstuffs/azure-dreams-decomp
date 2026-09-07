#include "common.h"

typedef struct {
    u8 b0;
    u8 b1;
    u16 h2;
    s32 w4;
} Record;

extern Record D_800CF720[];
extern u8 D_801131B8[];
extern s32 func_8008ACE8(s32, void *);
extern void func_8008ACAC(s32, s32, s32);

void func_8008AD90(s32 arg0, s32 arg1) {
    s32 temp_a1_2;
    s32 temp_s0;
    s32 temp_s1;
    s32 var_a0;
    Record *temp_a1;
    Record *temp_v1;
    s32 base;
    u8 *state;

    var_a0 = arg0;
    if (var_a0 != 0) {
        base = (s32)D_800CF720;
        state = D_801131B8;
        do {
            temp_a1 = (Record *)(var_a0 * 8 + base);
            temp_s1 = var_a0 - 1;
            temp_v1 = (Record *)(temp_s1 * 8 + base);
            temp_a1->b0 = temp_v1->b0;
            temp_a1->b1 = temp_v1->b1;
            temp_a1->h2 = temp_v1->h2;
            temp_s0 = temp_v1->w4;
            temp_a1->w4 = temp_s0;
            temp_a1_2 = *(s32 *)(state + 0x2c) + func_8008ACE8(temp_s1, temp_a1);
            func_8008ACAC(temp_a1_2 + arg1, temp_a1_2, temp_s0);
            var_a0 = temp_s1;
        } while (var_a0 != 0);
    }
}
