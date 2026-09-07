#include "common.h"

extern s32 func_80016250(s32);
extern void func_80018570(void);
extern s32 D_8001967C;
extern s32 D_8001970C[];

s32 func_80016A4C(s32 arg0, s32 arg1, s32 arg2) {
    s32 result = 0;

    if (arg2 == 8) {
        result = func_80016250(D_8001970C[D_8001967C]);
    }
    func_80018570();
    return result;
}
