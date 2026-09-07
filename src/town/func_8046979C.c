#include "common.h"

extern void func_8001A1A0(s32, s32 *);
extern s32 D_80017AAC[];
extern s32 D_80017AC4[];
extern s32 D_80017CE0[];

s32 func_8001A79C(void) {
    s32 *value = D_80017CE0;

    func_8001A1A0(value[0], D_80017AAC);
    func_8001A1A0(value[0] + 0x14, D_80017AC4);
    return value[0];
}
