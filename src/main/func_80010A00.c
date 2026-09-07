#include "common.h"

extern void func_800239B0(void *arg0);
extern s32 D_800814A0[];

void func_80023A00(s32 arg0) {
    void *temp_s0;

    if (arg0 != 0) {
        temp_s0 = (void *) (arg0 + 0x20);
        func_800239B0(temp_s0);
        *(u16 *) ((s8 *) temp_s0 - 2) = *(u16 *) ((s8 *) temp_s0 - 2) | 0x8000;
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
