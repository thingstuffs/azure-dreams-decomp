#include "common.h"
#include "engine/effect.h"
#include "engine/graphics.h"
#include "engine/text.h"

typedef struct S_8004EC20 {
    u8 pad00[4];
    s32 idx;       /* 0x4: index into D_80071654 callback table */
    u8 b8;         /* 0x8 */
    u8 b9;         /* 0x9 */
} S_8004EC20;

extern void *(*effect_state_callbacks[])(void *);

/* If both flags are set, wait for readiness and return the selected callback's result; otherwise return zero. */
void *dispatch_after_controller_release(void *data) {
    S_8004EC20 *dispatch = data;
    void *result = 0;

    if (dispatch->b8 != 0) {
        if (dispatch->b9 != 0) {
            while (pad_both_key_states_clear() == 0) {
                update_vsync_frame_id(2);
            }
            result = effect_state_callbacks[dispatch->idx]((u8 *)dispatch - 0x20);
        }
    }
    return result;
}
