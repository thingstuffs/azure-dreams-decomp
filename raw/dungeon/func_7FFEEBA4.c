#include "common.h"

extern int D_800814A0[];
extern void func_8008C28C(s32);
extern s32 D_800CFCA8;

void func_8008C304(void *arg0) {
    s32 temp_v0;

    func_8008C28C(*(s32 *)arg0);
    temp_v0 = *(s32 *)arg0 + 1;
    *(s32 *)arg0 = temp_v0;
    if (temp_v0 >= 0x80) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800CFCA8 = 0;
        D_800814A0[0] |= 0x8000;
    }
}
