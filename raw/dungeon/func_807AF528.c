#include "common.h"

extern s16 D_80083780[];
void func_800F6DF4(void) __attribute__((noreturn));

s32 func_807AF528(s16 *arg0)
{
    register s32 dispatch ASM_REG("$2");

    if (D_80083780[1] == arg0[1]) {
        if (D_80083780[3] != arg0[3]) {
            goto compare;
        }
        dispatch = 9;
        ASM_TAILSLOT_PIN(dispatch);
        func_800F6DF4();
    }

    compare:
    if (D_80083780[1] < arg0[1]) {
        if (D_80083780[3] < arg0[3]) {
            return 5;
        } else {
            if (arg0[3] < D_80083780[3]) {
                return 3;
            }
            dispatch = 4;
            ASM_TAILSLOT_PIN(dispatch);
            func_800F6DF4();
        }
    }

    if (arg0[1] < D_80083780[1]) {
        if (D_80083780[3] < arg0[3]) {
            return 7;
        }
        dispatch = arg0[3] < D_80083780[3];
        ASM_TAILSLOT_PIN(dispatch);
        func_800F6DF4();
    }

    if (D_80083780[3] < arg0[3]) {
        return 6;
    } else {
        dispatch = (arg0[3] < D_80083780[3]) * 2;
        ASM_TAILSLOT_PIN(dispatch);
        func_800F6DF4();
    }
}
