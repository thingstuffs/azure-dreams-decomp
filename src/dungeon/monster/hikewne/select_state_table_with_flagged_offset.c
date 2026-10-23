#include "common.h"
#include "dungeon/actor.h"
#include "shared/dungeon_status.h"

extern s32 advance_status_timers();
extern s32 update_actor_movement_to_tile();
extern s32 spend_actor_mp();


extern s32 hikewne_action_resume_address[];

/* Selects the state table after a successful target check and applies the flagged offset. */
void select_state_table_with_flagged_offset(void *state, s32 unused, s32 source, s32 target) {
    if (update_actor_movement_to_tile() != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = hikewne_action_resume_address;
            if (g_dungeon_status.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
