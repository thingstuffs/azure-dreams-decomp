#include "common.h"

extern u8 *D_8001E950;
extern s32 D_8001E954[];

s32 func_8001A2F0(void);
u8 func_8001A3E8(void);
s32 func_8001BC60(s32);

void func_8001BC98(void)
{
    D_8001E950[2] = 0xFF;
    if (func_8001A2F0() != 0) {
        D_8001E950[4] = func_8001A3E8();
        D_8001E950[5] = 2;
        D_8001E954[0] = func_8001BC60(D_8001E950[4]);
    } else {
        D_8001E950[5] = 1;
    }
}
