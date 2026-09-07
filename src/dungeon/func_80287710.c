#include "common.h"

extern s32 D_8001F660;
extern u8 D_8001F6A0;
extern u8 D_8001F6A4[4];
extern u8 D_8001F6E8[];

void func_8001A710(void) {
    s32 i;

    D_8001F6A4[0] = D_8001F6A4[1] = D_8001F6A4[2] = D_8001F6A4[3] = 0;
    D_8001F6A0 = D_8001F660;

    for (i = D_8001F660 - 1; i >= 0; i--) {
        u8* entry = &D_8001F6E8[i];

        entry[0] = 0;
        entry[4] = 0;
    }
}
