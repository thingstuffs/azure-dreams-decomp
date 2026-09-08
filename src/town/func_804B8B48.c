#include "common.h"

typedef struct TownState {
    s32 mode;
    s32 value;
} TownState;

typedef struct TownContext {
    u8 pad_00[0x1C];
    TownState *state;
    u8 *calls;
} TownContext;

typedef s32 (*TownCall1)(s32);
typedef s32 (*TownCall2)(s32, TownState *);

extern s8 D_80016000[];

s32 func_80017348(void) {
    TownContext **context_ptr;
    s32 saved_value;

    context_ptr = (TownContext **)D_80016000;

    {
        TownContext *context_first;
        u8 *calls_first;

        context_first = *context_ptr;
        calls_first = context_first->calls;
        (*(TownCall1 *)(calls_first + 0x258))(10);
    }

    {
        TownContext *context_second;
        u8 *calls_second;
        TownState *state_second;

        context_second = *context_ptr;
        calls_second = *(u8 * volatile *)&context_second->calls;
        state_second = *(TownState * volatile *)&context_second->state;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        saved_value = state_second->value;
        (*(TownCall2 *)(calls_second + 0x248))(1, state_second);
    }

    {
        TownContext *context_third;
        u8 *calls_third;

        context_third = *context_ptr;
        calls_third = context_third->calls;
        (*(TownCall1 *)(calls_third + 0x244))(1);
    }

    {
        TownContext *context_final;
        TownState *state_final;
        s32 new_value;

        context_final = *context_ptr;
        state_final = context_final->state;
        if (state_final->mode != 3) {
            return 0;
        }
        if (saved_value < state_final->value) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            new_value = saved_value + 0x30;
        } else {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            new_value = saved_value - 0x30;
        }
        state_final->value = new_value;
    }
    return 1;
}

/* MECHANISM: Per-call block-local roots, callback bases, and state pointers preserve
   retail's v0/v1/a1/a0 lifetimes in the natural 0x20 s0/s1/ra frame. Ordered volatile
   reads plus post-read and dual arm-entry fences restore the jalr slot and beqz/nop/j merge. */
