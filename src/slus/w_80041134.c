#include "common.h"

extern s32 D_80083C68[8];
extern s32 *D_800814E0;

/* Removes the first matching value from the zero-terminated list and backs up its append cursor. */
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
