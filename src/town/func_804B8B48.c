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

/* Run town callbacks and, in mode 3, set the value to its previous value plus or minus 0x30. */
s32 func_80017348(void) {
    TownContext **context_ptr;
    s32 previous_value;

    context_ptr = (TownContext **)D_80016000;

    {
        TownContext *context;
        u8 *calls;

        context = *context_ptr;
        calls = context->calls;
        (*(TownCall1 *)(calls + 0x258))(10);
    }

    {
        TownContext *context;
        u8 *calls;
        TownState *state;

        context = *context_ptr;
        calls = *(u8 * volatile *)&context->calls;
        state = *(TownState * volatile *)&context->state;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        previous_value = state->value;
        (*(TownCall2 *)(calls + 0x248))(1, state);
    }

    {
        TownContext *context;
        u8 *calls;

        context = *context_ptr;
        calls = context->calls;
        (*(TownCall1 *)(calls + 0x244))(1);
    }

    {
        TownContext *context;
        TownState *state;
        s32 adjusted_value;

        context = *context_ptr;
        state = context->state;
        if (state->mode != 3) {
            return 0;
        }
        if (previous_value < state->value) {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            adjusted_value = previous_value + 0x30;
        } else {
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            adjusted_value = previous_value - 0x30;
        }
        state->value = adjusted_value;
    }
    return 1;
}
