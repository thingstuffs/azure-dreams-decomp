#include "common.h"
#include "shared/dungeon_status.h"



s32 advance_status_timers();
s32 update_actor_movement_to_tile();
void spend_actor_mp();
s32 check_actor_floor_trap();
extern s32 D_80171514;

typedef struct S_80172474_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
} S_80172474_0;   /* entity in run_actor_callbacks_and_adjust_global_flag */

/* Runs actor callbacks, updates entity state on success, and applies the global flag adjustment. */
void run_actor_callbacks_and_adjust_global_flag(void *entity_ptr, s32 unused, s32 check_arg, s32 actor_arg)
{
    S_80172474_0 *entity = entity_ptr;
    s32 check_value = check_arg;
    s32 actor = actor_arg;

    if (update_actor_movement_to_tile() != 0) {
        spend_actor_mp(actor, 0);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(check_value, actor) << 0x10) <= 0) {
            return;
        }
        do {
            entity->unk_8C = &D_80171514;
        } while (0);
    }
    if (g_dungeon_status.flags & 0x80) {
        entity->unk_92 = -0x20;
    }
}
