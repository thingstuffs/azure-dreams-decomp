#include "common.h"
#include "shared/dungeon_status.h"

extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void);
extern void begin_ready_actor_directional_action(s32, s32, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);

/* Updates the actor state, consumes completed counts, and dispatches its action. */
void dispatch_actor_action_2(s32 actor, s32 action_arg, s32 action_data, u8 *state) {
    s16 old_count;

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (*(s32 *)(state + 0x1C) & 0x100) {
            begin_pushed_actor_move();
            return;
        }
        if (*(u8 *)(actor + 0x9A) != 0xE) {
            *(u8 *)(actor + 0x9A) = 0xE;
        }
    }
    if (*(s8 *)(state + 0x6D) > 0) {
        old_count = (s8)(state[0x6D] + 0);
        *(s32 *)(state + 0x60) = 0;
        update_actor_status_and_food(state);
        if ((old_count != 0) && (*(s8 *)(state + 0x6D) == 0)) {
            *(u8 *)(state + 0x28) -= 1;
        }
        if (*(u8 *)(state + 0x28) == 0) {
            g_dungeon_status.unk_10 = state - 0x20;
            begin_actor_display_action(actor, action_arg, action_data, 0);
            return;
        }
    }
    if (*(s16 *)(state + 0x64) != 0) {
        begin_ready_actor_directional_action(actor, action_arg, action_data, 0);
    }
}
