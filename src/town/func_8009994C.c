#include "common.h"

void func_800970AC(s32 arg0, u8 *arg1) {
    if (arg0 & 1) {
        arg1[0x37] = 1;
    } else {
        if (arg0 & 0x10) {
            arg1[0x36] = 1;
        }
    }
    if (arg0 & 0x100) {
        arg1[0x39] = 1;
        return;
    }
    if (arg0 & 0x1000) {
        arg1[0x38] = 1;
    }
}
