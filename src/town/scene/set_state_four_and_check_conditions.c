#include "script_symbols.h"
#include "common.h"

extern s32 func_800198D0();

typedef struct {
    s32 value;
    s32 pad[2];
} D_80019BB0_t;

extern D_80019BB0_t D_80019BB0;

/* Set state 4 and return whether check 0x3FE fails or check 0x3FF succeeds. */
s32 set_state_four_and_check_conditions(void) {
    s32 result;
    s32 ret;

    D_80019BB0.value = 4;
    if (func_800198D0(F_sbs01_pad09) != 0) {
        result = func_800198D0(F_sbs01_pad10);
        ret = 0;
        if (result == 0) {
            return ret;
        }
    }
    ret = 1;

    return ret;
}

/* MECHANISM: The post-call ret local supplies $zero in the branch delay slot and avoids an s-reg. */
