#include "common.h"
#include "engine/effect/resource_transition.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/text.h"

extern void *(*effect_state_callbacks[])(void *);

/* If both flags are set, wait for readiness and return the selected callback's result; otherwise return zero. */
void *dispatch_after_controller_release(void *data) {
    ResourceTransitionBody *dispatch = data;
    void *result = 0;

    if (dispatch->image_ready != 0) {
        if (dispatch->data_ready != 0) {
            while (pad_both_key_states_clear() == 0) {
                update_vsync_frame_id(2);
            }
            result = effect_state_callbacks[dispatch->callback_index]((u8 *)dispatch - 0x20);
        }
    }
    return result;
}
