#include "common.h"

typedef s32 (*Callback1)(s32);
typedef s32 (*Callback2)(s32, void *);

extern s8 D_80016000[];

/* Runs object callbacks and adjusts a type-3 state value if it lies within the saved-value window. */
s32 func_80017098(void) {
    s8 *object_slot;
    void *initial_state;
    void *updated_state;
    s32 saved_value;
    s32 current_value;

    object_slot = D_80016000;
    (*(Callback1 *)((s8 *)*(void **)((s8 *)*(void **)object_slot + 0x20) + 0x258))(15);

    {
        void *object;
        void *methods;

        object = *(void **)object_slot;
        do { methods = *(void * volatile *)((s8 *)object + 0x20); } while (0);
        initial_state = *(void * volatile *)((s8 *)object + 0x1C);
        saved_value = *(s32 *)((s8 *)initial_state + 4);
        (*(Callback2 *)((s8 *)methods + 0x248))(1, initial_state);
    }

    (*(Callback1 *)((s8 *)*(void **)((s8 *)*(void **)object_slot + 0x20) + 0x244))(1);

    updated_state = *(void **)((s8 *)*(void **)object_slot + 0x1C);
    if (*(s32 *)updated_state != 3) {
        return 0;
    }

    current_value = *(s32 *)((s8 *)updated_state + 4);
    saved_value -= 0x40;
    if ((saved_value < current_value) && (current_value < saved_value + 0x80)) {
        *(s32 *)((s8 *)updated_state + 4) = saved_value;
        return 1;
    }
    return 0;
}
