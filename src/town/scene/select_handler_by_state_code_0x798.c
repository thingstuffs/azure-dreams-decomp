#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef s32 (*Callback1)(s32);
typedef s32 (*Callback2)(s32, void *);


/* Runs object callbacks and adjusts a type-3 state value if it lies within the saved-value window. */
s32 select_handler_by_state_code_0x798(void) {
    Rec_D_80016000 **object_slot;
    TownPositionState *initial_state;
    TownPositionState *updated_state;
    s32 saved_value;
    s32 current_value;

    object_slot = &D_80016000;
    ((Callback1)(*object_slot)->unk_20->callback_258)(15);

    {
        Rec_D_80016000 *object;
        TownServiceTable *methods;

        object = *object_slot;
        do {
            methods = object->unk_20;
        } while (0);
        initial_state = object->unk_1C;
        saved_value = initial_state->x;
        ((Callback2)methods->callback_248)(1, initial_state);
    }

    ((Callback1)(*object_slot)->unk_20->callback_244)(1);

    updated_state = (*object_slot)->unk_1C;
    if (updated_state->unk_00 != 3) {
        return 0;
    }

    current_value = updated_state->x;
    saved_value -= 0x40;
    if ((saved_value < current_value) && (current_value < saved_value + 0x80)) {
        updated_state->x = saved_value;
        return 1;
    }
    return 0;
}
