#include "common.h"

extern s32 func_800162F8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_8001C769[];
extern u8 D_8001D244[];

/* Returns the shared result address when the input check succeeds. */
void *func_80016CAC(s32 check_input_a, s32 check_input_b, s32 check_input_c) {
    if (func_800162F8(check_input_a, check_input_b, check_input_c) != 0) {
        return D_8001D244;
    }
    return D_8001C769;
}
