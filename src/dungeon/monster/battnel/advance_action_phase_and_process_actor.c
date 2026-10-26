#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

extern void unlink_entity_node(void *node);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, s32 flag_mask);
extern void distribute_experience_and_report_gains(void *entity);
extern void * detach_record_and_update_slot_state(void *record);
extern void play_sound_if_enabled(s32 query_value);


/* Advance the action phase and process the actor when the tile flags are set. */
void advance_action_phase_and_process_actor(ActorRecord *action, ObjectPosition *unused, SpriteFrameState *tile, ActorRecord *actor) {
    s32 status_flags;
    s32 actor_flags;
    s32 strength;
    s32 x;
    s32 y;
    u8 phase;

    phase = action->action_phase;
    switch (phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        status_flags = actor->flags14;
        if (status_flags & 0x4000) {
            if (!(status_flags & 0x20000000)) {
                announce_familiar_defeat(actor);
            }
        }

        action->action_phase++;
        play_sound_if_enabled(0x805);
        /* fall through */
    case 1:
        if (tile->flags & 0xE000) {
            if ((g_dungeon_status.pending_display_owner) == ((u8 *)actor - 0x20)) {
                *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
            }

            distribute_experience_and_report_gains(actor);
            detach_record_and_update_slot_state(actor);

            actor_flags = actor->flags1C;
            x = tile->tile_x;
            y = tile->tile_y;
            strength = 0x3000;
            if (actor_flags & 0x2000) {
                strength = 0x300;
            }
            update_map_cell_flags_with_item_limit(x, y, strength);
            unlink_entity_node(actor);

            *(u16 *)(((u8 *)actor - 2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    }
}
