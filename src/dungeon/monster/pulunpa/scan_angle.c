/* Pulunpa target scanning and nearby directional action selection. */
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80175E6C_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80175E6C_5;

typedef struct S_80175E6C_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80175E6C_6_pre;   /* the 0x14 bytes before ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv in select_nearby_target_and_start_action, addressed as ((Rec_D_800E3D7C *)arg3)->unk_60.as_pv[-1] */

void select_sprite_entry(void *, u8, s32);
#include "dungeon/player/object/action_state.h"
#include "dungeon/item.h"
void update_actor_status_and_mp(ActorRecord *entity);
void build_and_display_encoded_message(ActorRecord *);
extern u8 D_80176348[];

/*
 * Converts the direction index to an angle by shifting it left nine bits, returning the signed low
 * halfword.
 */
static __inline__ s16 scan_angle(s32 direction)
{
    return direction << 9;
}

/* Selects a neighboring target and starts an action when the reference entity is nearby. */
s32 select_nearby_target_and_start_action(ActorRecord *action_state, ObjectPosition *unused, SpriteFrameState *actor_pos_arg, ActorRecord *actor) {
    u16 distance;
    s32 neighbor_flags;
    s32 direction;
    u16 reference_found;
    s32 result;
    ActorRecord *neighbor;
    S_80175E6C_5 *target_pos;
    void *target;

    target = NULL;
    actor->movement_queue_state = (u8) (actor->movement_queue_state & 0x7F);
    reference_found = (s32) target;
    if ((g_dungeon_status.flags & 0x2008) || ((has_pending_actor_or_turn_action(actor) << 0x10) != 0)) {
        result = -1;
        return result;
    }
    for (direction = 0; direction < 8; direction++) {
    neighbor = probe_directional_neighbor(actor, actor_pos_arg->tile_x, actor_pos_arg->tile_y,
        scan_angle(direction));
    if (neighbor != NULL) {
        if (neighbor == ((u8 *)dungeon_actor_ring_anchor)) {
            reference_found = 1;
        } else {
            neighbor_flags = neighbor->flags14;
            if (neighbor_flags & 0x4000) {
                if (!(neighbor_flags & 0x20000000)) {
                    target = neighbor;
                }
            }
        }
    }
    }
    if ((target != NULL) && (reference_found & 0xFFFF)) {
        reference_found = (s16) (g_dungeon_status.activity_counts.parts.pending_action_count + 1);
        g_dungeon_status.activity_counts.parts.pending_action_count = reference_found;
        actor->target = target;
        update_actor_status_and_mp(target);
        action_state->action_id.s = 0x17;
        action_state->action_phase.s = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        target_pos = ((S_80175E6C_6_pre *)actor->target)[-1].unk_00;
        actor->facing = get_rounded_facing_and_rounding_flag(actor_pos_arg->tile_x,
            actor_pos_arg->tile_y, target_pos->unk_24,
            target_pos->unk_25, &distance);
        actor_pos_arg->frameTable = D_80176348;
        select_sprite_entry(actor_pos_arg, D_80176348[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100)
            >> 9) & 7], 0);
        build_and_display_encoded_message(actor);
        result = 1;
        return result;
    }
    result = 0;
    return result;
}
