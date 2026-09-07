#include "common.h"

extern s32 func_80042900(void *arg0, s32 arg1);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_80099844(void *arg0, void *arg1);
extern s8 D_800E0DF5[];

s32 func_800B6228(void *arg0) {
    if ((func_80042900(arg0, 2) << 16) != 0) {
        func_80042B68(arg0, 2);
        func_80099844(arg0, D_800E0DF5);
        return 1;
    }
    return 1;
}
