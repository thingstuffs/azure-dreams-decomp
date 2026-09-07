#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern void func_80404DBC(s32 arg0);
extern void func_80403D24(s32 arg0);
extern void func_804059A8(s32 arg0);
extern void func_80404570(s32 arg0);

/* Dual symbols at the same address force load-via-v1 / store-via-at RMW
 * (retail uses separate %hi materializations, not a reused base reg). */
extern s32 D_8008DAB4[4];
extern s32 D_8008DAB4_2[4];
__asm__(".set D_8008DAB4, 0x8008DAB4");
__asm__(".set D_8008DAB4_2, 0x8008DAB4");

void func_8001F720(void *arg0) {
    /* Pin walker to $s0 — pure C assigns it $s1/$s2 under 2.7.2. */
    register s32 *var_s0 ASM_REG("$16");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 var_s1;
    s32 temp_a0;
    u16 temp_v0;
    s32 temp_v1;

    var_s0 = (s32 *)((u8 *)arg0 + 0x20);
    if (arg0 != NULL) {
        var_s1 = 0;
        func_80404DBC(*(s32 *)((u8 *)arg0 + 0x20));
        func_80403D24(*(s32 *)((u8 *)arg0 + 0x38));
        func_804059A8(*(s32 *)((u8 *)arg0 + 0x3C));
        do {
            temp_a0 = *(s32 *)((u8 *)var_s0 + 4);
            var_s0 = (s32 *)((u8 *)var_s0 + 4);
            var_s1 += 1;
            func_80404570(temp_a0);
        } while (var_s1 < 5);
        temp_v0 = *(u16 *)((u8 *)arg0 + 0x1E);
        temp_v1 = D_8008DAB4[0];
        temp_v0 |= 0x8000;
        temp_v1 |= 0x8000;
        *(u16 *)((u8 *)arg0 + 0x1E) = temp_v0;
        D_8008DAB4_2[0] = temp_v1;
    }
}
