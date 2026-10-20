#include "common.h"
#include "shared/dungeon_status.h"

extern void update_actor_status_and_food(void *);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern s32 begin_ready_actor_directional_action(void *, s32, void *, s32);

/* Processes active status, counts completed transitions, and dispatches follow-up work. */
void advance_actor_status_turn_second(s32 dispatch_arg0, s32 dispatch_arg1, s32 dispatch_arg2, u8 *state) {
    s16 previous_status;

    if ((s8)state[0x6D] > 0) {
        previous_status = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        update_actor_status_and_food(state);
        if (previous_status != 0 && *(s8 *)(state + 0x6D) == 0) {
            state[0x28]--;
        }
        if (state[0x28] == 0) {
            g_dungeon_status.unk_10 = state - 0x20;
            begin_actor_display_action(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        begin_ready_actor_directional_action(dispatch_arg0, dispatch_arg1, dispatch_arg2, 0);
    }
}
