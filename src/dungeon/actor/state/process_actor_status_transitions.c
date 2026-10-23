#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"

extern void update_actor_status_and_mp(void *);
extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
extern void begin_ready_actor_directional_action(s32, s32, s32, s32);

/* Processes active status, counts completed transitions, and dispatches follow-up work. */
void process_actor_status_transitions(s32 actor, s32 action_context, s32 sprite, u8 *state) {
    s16 previous_status;

    if ((s8)state[0x6D] > 0) {
        previous_status = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        update_actor_status_and_mp(state);
        if (previous_status != 0 && *(s8 *)(state + 0x6D) == 0) {
            state[0x28]--;
        }
        if (state[0x28] == 0) {
            g_dungeon_status.pending_display_owner = state - 0x20;
            begin_actor_display_action(actor, action_context, sprite, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        begin_ready_actor_directional_action(actor, action_context, sprite, 0);
    }
}
