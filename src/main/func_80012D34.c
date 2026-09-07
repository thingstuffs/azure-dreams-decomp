#include "common.h"

/* Sibling of func_8004FE78/func_8004F52C/func_8004EE90/... (D_800814A0 global
 * flags-word family). Precomputes a base pointer to a0+0x20 (used before the
 * NULL check, matching target scheduling), calls func_8004F52C on the pointer
 * stored at a0+0x20 (that pointee has its own 0x8000 flags bit at its own
 * offset 0x1E, set inside func_8004F52C itself), calls func_80023A00 and
 * func_80024EEC on the words at a0+0x38/a0+0x3C (addressed relative to the
 * a0+0x20 base pointer), walks 5 handle words at a0+0x24..0x34 through
 * func_80024184, and finally sets the 0x8000 bit on a0's own 0x1E flags field
 * and on the global flags word D_800814A0. */

typedef struct UnkStruct1E {
    u8 pad[0x1E];
    u16 flags;
} UnkStruct1E;

extern int D_800814A0;

extern void func_8004F52C(UnkStruct1E *a0);
extern void func_80023A00(s32 arg0);
extern void func_80024EEC(s32 arg0);
extern void func_80024184(s32 arg0);

void func_80025D34(UnkStruct1E *a0)
{
    s32 temp_a0;
    s32 var_s1;
    void *var_s0;

    var_s0 = (u8 *)a0 + 0x20;
    if (a0 != 0) {
        var_s1 = 0;
        func_8004F52C(*(UnkStruct1E **)((u8 *)a0 + 0x20));
        func_80023A00(*(s32 *)((u8 *)var_s0 + 0x18));
        func_80024EEC(*(s32 *)((u8 *)var_s0 + 0x1C));
        do {
            temp_a0 = *(s32 *)((u8 *)var_s0 + 4);
            var_s0 = (u8 *)var_s0 + 4;
            var_s1 += 1;
            func_80024184(temp_a0);
        } while (var_s1 < 5);
        a0->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
