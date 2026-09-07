#include "common.h"

extern void func_800970D0(void);
extern void func_800970F4(void);

void func_800970AC(s32 arg0, u8 *arg1) {
    if (arg0 & 1) {
        arg1[0x37] = 1;
        return func_800970D0();
    }
    if (arg0 & 0x10) {
        arg1[0x36] = 1;
    }
    if (arg0 & 0x100) {
        arg1[0x39] = 1;
        return func_800970F4();
    }
    if (arg0 & 0x1000) {
        arg1[0x38] = 1;
    }
}
