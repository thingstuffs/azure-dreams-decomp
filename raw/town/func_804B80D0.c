#include "common.h"

#define FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001611C(void);
extern s32 func_80018854(s32);
extern s32 func_800188CC(s32);
extern s32 func_8001894C(s32);
extern void *D_80016000;
extern s16 D_80018AEA;

s32 func_800168D0(void) {
    s32 ret;

    func_8001611C();
    if (func_8001894C(D_80018AEA) == 0) {
        func_80018854(0x511);
        if (FIELD(((FIELD(D_80016000, s32 *, 8) * 8) +
                   FIELD(D_80016000, s32 *, 0x40)),
                  u8 *, 2) == 0) {
            func_800188CC(0x514);
        }
    }
    if (func_8001894C(0x514) == 0) {
        ret = func_8001894C(0x11FC) == 0;
    } else {
        ret = 1;
    }
    return ret;
}
