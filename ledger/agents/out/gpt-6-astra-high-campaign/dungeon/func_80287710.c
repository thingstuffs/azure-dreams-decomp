#include "common.h"

extern s32 D_8001F660;
extern u8 D_8001F6A0;
extern u8 D_8001F6A4[4];
extern u8 D_8001F6E8[];

/* Clears the status bytes and entry arrays and resets the remaining count. */
void func_8001A710(void) {
    s32 entry_index;

    D_8001F6A4[0] = D_8001F6A4[1] = D_8001F6A4[2] = D_8001F6A4[3] = 0;
    D_8001F6A0 = D_8001F660;

    for (entry_index = D_8001F660 - 1; entry_index >= 0; entry_index--) {
        u8* entry = &D_8001F6E8[entry_index];

        entry[0] = 0;
        entry[4] = 0;
    }
}
