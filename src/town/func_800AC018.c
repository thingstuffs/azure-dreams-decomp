#include "common.h"

extern s32 func_80033AA8(s32 arg0);
extern s32 func_8009F88C(s32 arg0, s32 arg1);
extern int D_800814A0;

void func_800A9778(u16 *arg0) {
    if (func_8009F88C(0xC, 0xF) != 0) {
        func_80033AA8(0xAB);
        arg0[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
