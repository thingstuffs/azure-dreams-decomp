#include "common.h"

extern void func_80093D48(void *, s32, s32);
extern void func_8009451C(void *, s32, s32);
extern s32 func_80095840(void *, s32 *);
extern s32 D_800CFCB4[];

void func_80093B00(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_v1;
    s32 temp_v0;

    temp_v1 = *(s32 *)((u8 *)arg0 + 0x2C);
    if (temp_v1 != 0) {
        D_800CFCB4[4] = temp_v1;
        D_800CFCB4[6] = 0;
        func_8009451C(arg0, arg1, arg2);
    } else {
        temp_v0 = func_80095840(arg0, D_800CFCB4);
        if (temp_v0 != 0) {
            if (temp_v0 == 2) {
                func_8009451C(arg0, arg1, arg2);
            } else {
                func_80093D48(arg0, arg1, arg2);
            }
        } else {
            func_80093D48(arg0, arg1, arg2);
        }
    }
}
