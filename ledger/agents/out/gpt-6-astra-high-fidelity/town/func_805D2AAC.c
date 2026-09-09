#include "common.h"

extern s32 D_80019AFC;

extern s32 func_800169B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_80016A00(s32 arg0, s32 arg1);
extern s32 func_80016A4C(void);

s32 func_80016AAC(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_80019AFC == 0) {
        return func_800169B4(arg0, arg1, arg2, arg3);
    }
    if (D_80019AFC == 1) {
        return func_80016A00(arg0, arg1);
    }
    if (D_80019AFC == 3) {
        return func_80016A4C();
    }
    return 0;
}
