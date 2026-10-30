/* Dispatch state callbacks by mode (G00544). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A688. */
#include "town/player/state_callback_g00544.h"
#include "town/player.h"
#include "engine/script.h"

/* Dispatches the player action or indexed callback according to script activity and the signed mode. */
void dispatch_state_callback_by_mode(s32 value, void *ptr, void *ptr2, s32 unused) {
    u8 *state;
    Callback callback;
    s8 status;

    if (service_script_controller() == 0) {
        ((Callback)town_player_action_callback[0])(value, ptr, ptr2);
        return;
    }
    state = object_index_slots;
    status = *(s8 *)(state + 8);
    if (status >= 2) {
        ((Callback)D_800D0508[status])(value, ptr, ptr2);
        return;
    }
    if (status < 0) {
        callback = (Callback)town_player_action_callback[0];
        *(s8 *)(state + 8) = 0;
        callback(value, ptr, ptr2);
    }
}

/* Forward the value, context, data, and mode to dispatch_state_callback_by_mode. */
void forward_value_context_data_mode(s32 value, void *context, void *data, s32 mode) {
    dispatch_state_callback_by_mode(value, context, data, mode);
}
