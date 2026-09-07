#include "common.h"

extern s32 D_80019AFC;

extern s32 func_800169B4(void);
extern s32 func_80016A00(void);
extern s32 func_80016A4C(void);

s32 func_80016AAC(void) {
    if (D_80019AFC == 0) {
        return func_800169B4();
    }
    if (D_80019AFC == 1) {
        return func_80016A00();
    }
    if (D_80019AFC == 3) {
        return func_80016A4C();
    }
    return 0;
}
