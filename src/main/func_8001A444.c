#include "common.h"

extern s32 func_8007C9C8(s32 arg0);

extern s32 D_80409270[];
extern s32 D_80409274[];
extern s32 D_80409278[];
extern s32 D_8040927C[];

s32 func_80401444(void) {
    s32 result;

    result = 0;
    if (func_8007C9C8(D_80409270[0]) != 0) {
        result = 1;
    } else {
        if (func_8007C9C8(D_80409274[0]) != 0) {
            result = 2;
        } else {
            if (func_8007C9C8(D_80409278[0]) != 0) {
                result = 3;
            } else {
                if (func_8007C9C8(D_8040927C[0]) != 0) {
                    result = 4;
                }
            }
        }
    }
    return result;
}
