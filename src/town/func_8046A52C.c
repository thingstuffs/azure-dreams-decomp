#include "common.h"

extern u8 *D_8001E950;

s32 func_8001A664();
void func_8001E578();

s32 func_8001B52C(void *arg0, s32 arg1) {
    s32 value;
    s32 base;

    if (D_8001E950[5] == 2) {
        value = func_8001A664(D_8001E950[4]);
        base = *(s32 *)((u8 *)arg0 + 0x10);
        *(s32 *)((arg1 << 4) + base + 8) = value;
        func_8001E578(0x402, base);
        return 0;
    }
    return 1;
}
