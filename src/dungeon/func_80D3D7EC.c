#include "common.h"
#include "shared/dungeon_status.h"

extern u32 update_actor_movement_to_tile(void);
extern void reduce_actor_food_meter(void *, s32);
extern void advance_status_timers(void *);
extern s32 check_actor_floor_trap(void *, void *);

extern u8 D_80171A80[];

/* Updates actor behavior and state fields according to mode and input. */
void update_actor_movement_state(void *state, s32 unused, void *action_arg, void *actor_arg)
{
    void *action_data = action_arg;
    void *actor = actor_arg;

    if (update_actor_movement_to_tile() != 0) {
        if (*(u8 *)((u8 *)state + 0xB5) == 0) {
            reduce_actor_food_meter(actor, 4);
            advance_status_timers(actor);
            if ((check_actor_floor_trap(action_data, actor) << 16) <= 0) {
                return;
            }
        } else {
            reduce_actor_food_meter(actor, 0x10);
            advance_status_timers(actor);
        }
        *(void **)((u8 *)state + 0x8C) = D_80171A80;
    }

    if (g_dungeon_status.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
        if (*(u8 *)((u8 *)state + 0xB5) != 0) {
            *(s16 *)((u8 *)state + 0x92) = 0;
        }
    }
}
