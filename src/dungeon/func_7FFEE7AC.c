#include "common.h"

extern int D_800814A0[];
void func_80033C84(void *);

void func_8008BF0C(void *arg0) {
    int val;
    func_80033C84(*(void **)arg0);
    ((u16 *)arg0)[-1] |= 0x8000;
    val = D_800814A0[0];
    ((s32 *)arg0)[-4] = 0;
    D_800814A0[0] = val | 0x8000;
}
