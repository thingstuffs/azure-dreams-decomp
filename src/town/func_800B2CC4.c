#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_800AE484();
extern M2C_UNK func_800AE4D4();
extern s32 func_800AF234();
extern M2C_UNK func_800B047C();

void func_800B0424(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_800AF234(((s32 *)arg0)[1], ((s32 *)arg0)[3]);
    if (temp_v0 == 1) {
        func_800AE4D4(((s32 *)arg0)[2]);
        return;
    }
    if (temp_v0 == 2) {
        func_800AE484(((s32 *)arg0)[2]);
        return;
    }
}
