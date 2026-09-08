#include "common.h"

extern s32 func_800189FC(void *arg0, s32 arg1);
extern s32 D_8001B210;
extern s32 D_8001B218[];

/* Stores the result of func_800189FC for D_8001B218 in D_8001B210. */
void func_804712E0(void) {
    D_8001B210 = func_800189FC(D_8001B218, 1);
}
