#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_func_800C9F34_arg0.h"
#include "dungeon/actor.h"



extern s32 check_entity_relation();
extern s8 find_active_rect_containing_point();
extern s32 can_entity_gain_level();
extern void advance_actor_along_path_points(void *motion, s32 unused, void *position, void *path);
#include "dungeon/actor/state.h"


typedef struct S_800C9F34_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800C9F34_3;   /* arg2 in dispatch_actor_behavior_state */


/* Updates entity action state and dispatches the appropriate handler. */
void dispatch_actor_behavior_state(Rec_func_800C9F34_arg0 *actor_state, s32 context, S_800C9F34_3 *position, ActorRecord *entity) {

    if (g_dungeon_status.flags & 0x1000) {
        actor_state->unk_9A.as_s8 = 0xE;
        advance_actor_along_path_points(actor_state, context, position, entity);
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        actor_state->unk_9A.as_s8 = 0xE;
        entity->flags1C =
            entity->flags1C | 0x40000;
        actor_state->unk_98 = actor_state->unk_98 & 0xFFF7;
        if (entity->hp == 0 || ((*(u16 *)0x80013714) & 8) != 0) {
            set_actor_action_state_eight(actor_state, context, position);
            return;
        }
        if ((can_entity_gain_level(entity) << 0x10) != 0) {
            if ((g_dungeon_status.active_actor == entity) &&
                (g_dungeon_status.activity_counts.parts.pending_action_count == 0) &&
                !(g_dungeon_status.flags & 8)) {
                entity->experience = 0;
                g_dungeon_status.active_actor = 0;
            }
            return;
        }
    }
    position->unk_26 = find_active_rect_containing_point(
        position->unk_24, position->unk_25);
    if ((entity->pending_turn_updates > 0) &&
        (!(g_dungeon_status.flags & 0x2000) ||
         ((check_entity_relation(entity,
            ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) == 0))) {
        choose_best_eligible_entry_for_actor(actor_state, context, position);
    }
}
