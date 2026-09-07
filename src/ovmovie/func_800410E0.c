#include "common.h"

extern void func_80177BC0(void);
extern s32 func_8017790C(void);
extern u32 func_80177CF0(void);

s32 func_800410E0(s32 arg0) {
    if (arg0 != 0) {
        return (func_80177CF0() >> 0x1D) & 1;
    }
    func_80177BC0();
    return func_8017790C();
}
