#include "common.h"

extern s32 D_80083C68[8];
extern s32 *D_800814E0;

/* Removes the first occurrence of arg0 from the zero-terminated int list
   D_80083C68, shifting later entries down by one slot, and decrements the
   D_800814E0 list-append cursor by one int. */
void func_80041134(s32 arg0) {
    s32 *sp = D_80083C68;
    if (*sp != 0) {
        do {
            if (*sp == arg0) {
                D_800814E0--;
                for (;;) {
                    *sp = sp[1];
                    sp++;
                    if (*sp == 0) {
                        return;
                    }
                }
            }
            sp++;
        } while (*sp != 0);
    }
}
