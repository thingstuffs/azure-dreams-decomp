#include "common.h"

extern s32 D_80083C68[8];
s32 *D_800814E0 = 0;

/* Initialize the zero-terminated list and its append cursor. */
void func_800410FC(void) {
    D_800814E0 = D_80083C68;
    D_80083C68[0] = 0;
}

/* Append a value and restore the zero terminator. */
void func_80041110(s32 value) {
    *D_800814E0 = value;
    D_800814E0++;
    *D_800814E0 = 0;
}

/* Remove the first matching value. */
void func_80041134(s32 value) {
    s32 *entry = D_80083C68;
    if (*entry != 0) {
        do {
            if (*entry == value) {
                D_800814E0--;
                for (;;) {
                    *entry = entry[1];
                    entry++;
                    if (*entry == 0) {
                        return;
                    }
                }
            }
            entry++;
        } while (*entry != 0);
    }
}
