#include "common.h"

extern void func_800A9A0C(void *);
extern s16 func_800ADDA0(s32, s32, void *, s32, s32, void *);
extern void func_8017405C(void *, s32, s32, void *);
extern u16 D_80083462;

/* Checks an object action, dispatches its update, and clears flags as needed. */
s32 func_80175C94(void *object, s32 query_x, s32 query_y, s32 action_override) {
    s32 saved_x = query_x;
    s32 saved_y = query_y;
    register s32 saved_override ASM_REG("$19") = action_override;   /* MATCH pin: keeps a statement from moving across a call/branch */
    void *saved_object = object;
    s32 next_state;
    s32 clear_result;
    s16 action_result;
    s32 override_bits;

    action_result = func_800ADDA0(saved_x, saved_y, saved_object, 3, 6,
                           (u8 *)saved_object + 0x9C);
    ASM_KEEP(saved_x);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(saved_y);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (action_result < 0) {
        goto return_zero;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
    override_bits = saved_override << 16;
    ASM_KEEP(saved_override);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    if (override_bits != 0) {
        goto call_block;
    }
    next_state = 0xE;
    if (action_result == 0) {
        goto zero_block;
    }
    if (action_result == 2) {
        goto call_block;
    }
    goto tail_block;

zero_block:
    *((s8 *)saved_object + 0x9A) = next_state;
    func_800A9A0C(saved_object);
    goto return_zero;

call_block:
    func_8017405C(saved_object, saved_x, saved_y, saved_object);
    goto return_zero;

tail_block:
    *((u8 *)saved_object + 0x71) &= 0x7F;
    if (D_80083462 & 8) {
        clear_result = 0;
        goto clear_halfword;
    }
    return 1;

clear_halfword:
    *(u16 *)((u8 *)saved_object + 0x46) &= 0x7FFF;
    return clear_result;

return_zero:
    return 0;
}

