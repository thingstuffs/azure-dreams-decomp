#include "common.h"

/* Searches a null-terminated array of 4-byte records pointed to by D_80081508 for a record whose first two bytes match the low 16 bits of a0/a1; returns 1 if found, else 0. */
typedef struct {
    u8 a;
    u8 b;
    u8 pad2;
    u8 pad3;
} S_80081508;

extern S_80081508 *D_80081508;

s32 func_800448BC(s32 a0, s32 a1) {
    u16 w0 = (u16)a0;
    u16 w1 = (u16)a1;
    S_80081508 *p = D_80081508;

    if (p->a != 0) {
        do {
            if (p->a == w0 && p->b == w1) {
                return 1;
            }
            p += 1;
        } while (p->a != 0);
    }
    return 0;
}
