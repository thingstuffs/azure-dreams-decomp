/* Dispatch state callbacks by mode. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A688. */
#include "town/player/state_callback_g00544.h"
#include "town/player.h"
#include "engine/script.h"

/* Dispatches the player action or indexed callback according to script activity and the signed mode. */
void dispatch_state_callback_by_mode(void *object, ObjectPosition *position, SpriteFrameState *sprite, s32 unused) {
    u8 *state;
    TownPlayerStateCallback callback;
    s8 status;

    if (service_script_controller() == 0) {
        ((TownPlayerStateCallback)town_player_action_callback[0])(object, position, sprite);
        return;
    }
    state = object_index_slots;
    status = *(s8 *)(state + 8);
    if (status >= 2) {
        slot_status_callbacks[status](object, position, sprite);
        return;
    }
    if (status < 0) {
        callback = (TownPlayerStateCallback)town_player_action_callback[0];
        *(s8 *)(state + 8) = 0;
        callback(object, position, sprite);
    }
}

/* Forward the value, context, data, and mode to dispatch_state_callback_by_mode. */
void forward_state_callback_dispatch(void *object, ObjectPosition *position, SpriteFrameState *sprite, s32 mode) {
    dispatch_state_callback_by_mode(object, position, sprite, mode);
}
