#include "common.h"
#include "shared/position_views.h"

/* extern */

typedef struct S_800CE2D4_0 {
    u8 pad_00[0x6C];
    u16 unk_6C;
    u8 pad_6E[0x16];
    s16 unk_84;
    s16 unk_86;
} S_800CE2D4_0;   /* arg0 in tick_countdown_toward_target */

   /* arg1 in tick_countdown_toward_target */


void apply_object_setup_and_update(void *object, s32 update_context, s32 setup_context);
/* Decrement the countdown and ease the current values toward their targets. */
void tick_countdown_toward_target(S_800CE2D4_0 *state, SignedPositionView *current, s32 context) {
    u16 ticks_left;
    u32 target_delta;

    ticks_left = state->unk_6C - 1;
    state->unk_6C = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        apply_object_setup_and_update(state, current, context);
    }
    current->x = (s16) ((u16) current->x + ((s32) (state->unk_84 - current->x) / 2));
    target_delta = state->unk_86 - current->y;
    current->z = (s16) ((u16) current->z + ((s32) (0 - current->z) / 2));
    current->y = (s16) ((u16) current->y + ((s32) (target_delta + (target_delta >> 0x1F)) >> 1));
}
