#include "common.h"

typedef void (*Func)(u32);

extern Func D_800294B8[];

void func_80025548(s32 *arg0) {
    s32 index = arg0[3];

    D_800294B8[index](arg0[index + 8]);
    arg0[-4] = 0;
}
