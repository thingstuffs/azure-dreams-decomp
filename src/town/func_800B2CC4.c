#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_800AE484();
extern M2C_UNK func_800AE4D4();
extern s32 func_800AF234();

/* Dispatch the request's payload according to its result code. */
void func_800B0424(void *request) {
    s32 result_code;

    result_code = func_800AF234(((s32 *)request)[1], ((s32 *)request)[3]);
    if (result_code == 1) {
        func_800AE4D4(((s32 *)request)[2]);
        return;
    }
    if (result_code == 2) {
        func_800AE484(((s32 *)request)[2]);
        return;
    }
}
