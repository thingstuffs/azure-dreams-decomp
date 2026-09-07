#include "common.h"

extern s16 D_80083780[];

s32 func_800F6D28(s16 *arg0)
{
    if (D_80083780[1] == arg0[1]) {
        if (D_80083780[3] != arg0[3]) {
            goto compare;
        }
        return 9;
    }

    compare:
    if (D_80083780[1] < arg0[1]) {
        if (D_80083780[3] < arg0[3]) {
            return 5;
        }
        if (arg0[3] < D_80083780[3]) {
            return 3;
        }
        return 4;
    }

    if (arg0[1] < D_80083780[1]) {
        if (D_80083780[3] < arg0[3]) {
            return 7;
        }
        return arg0[3] < D_80083780[3];
    }

    if (D_80083780[3] >= arg0[3]) {
        return (arg0[3] < D_80083780[3]) * 2;
    }
    return 6;
}
