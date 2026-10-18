#include "common.h"

extern void func_80017320(s32);
extern void func_80017398(s32);
extern s16 D_800175B4;

/* Advance the counter D_800175B4 (wrapping from 21 back to 9); at 8 or 20 call func_80017320(0x5DB), else func_80017398(0x5DB). */
void check_record_value_threshold(void) {
    D_800175B4++;
    if (D_800175B4 >= 21) {
        D_800175B4 = 9;
    }
    if (D_800175B4 == 8 || D_800175B4 == 20) {
        func_80017320(0x5DB);
    } else {
        func_80017398(0x5DB);
    }
}
