#include "common.h"

extern void func_800540A8(void);
extern void func_8004425C(s32 arg0);
extern s16 func_80053DA8(s32 arg0);

s32 func_800C1464(s32 arg0, s32 arg1) {
    func_800540A8();
    if (arg0 != 0) {
        func_8004425C((s16)arg0);
    }
    if (arg1 != 0) {
        func_80053DA8(arg1 & 0xFFFF);
    }
    return 1;
}
