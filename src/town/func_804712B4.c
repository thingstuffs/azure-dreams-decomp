#include "common.h"

extern s32 func_800189FC(void *, s32);
extern s32 D_8001B210;
extern s32 D_8001B218[];

void func_804712B4(void) {
    D_8001B210 = func_800189FC(D_8001B218, 0);
}
