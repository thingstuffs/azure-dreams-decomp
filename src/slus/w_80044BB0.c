#include "common.h"

#define U16_AT(base, offset) (*(u16 *)((s8 *)(base) + (offset)))
#define PTR_AT(base, offset) (*(void **)((s8 *)(base) + (offset)))

extern void func_80044D24(void *, void *, s32);

s32 func_80044BB0(void *arg0, void *arg1, void *arg2) {
    void *var_s0;
    void *var_v1;
    void *var_a1;
    void *next;
    u16 *scratch;

    var_s0 = arg0;
    var_v1 = arg1;
    var_a1 = arg2;
    scratch = (u16 *)0x1F800000;

loop:
    if (!(U16_AT(var_a1, 0x14) & 0x80)) {
        scratch[0] = U16_AT(var_v1, 2);
        scratch[1] = U16_AT(var_v1, 6);
        func_80044D24(var_s0, var_a1, (s16)(U16_AT(var_v1, 0xA) + U16_AT(var_a1, 6)));
    }

    next = PTR_AT(var_s0, -8);
    var_s0 = (s8 *)next + 0x20;
    if (next != 0) {
        var_v1 = PTR_AT(next, 8);
        var_a1 = PTR_AT(next, 0xC);
        goto loop;
    }

    return 0;
}
