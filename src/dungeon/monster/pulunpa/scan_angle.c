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

typedef struct S_80175E6C_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80175E6C_2;

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
void *probe_directional_neighbor(void *, u8, u8, s16);
s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
#include "dungeon/player/object/action_state.h"
void update_actor_status_and_mp(void *);
void build_and_display_encoded_message(void *);
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
s32 select_nearby_target_and_start_action(void *action_state, void *unused, SpriteFrameState *actor_pos_arg, void *actor) {
    u16 distance;
    s32 neighbor_flags;
    s32 direction;
    u16 reference_found;
    s32 result;
    void *neighbor;
    void *target_pos;
    void *target;

    target = NULL;
    ((EntityRec *)actor)->unk_71 = (u8) (((EntityRec *)actor)->unk_71 & 0x7F);
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
            neighbor_flags = ((S_80175E6C_2 *)neighbor)->unk_14;
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
        ((EntityRec *)actor)->target = target;
        update_actor_status_and_mp(target);
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9A.as_s8 = 0x17;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_9B.as_s8 = 0;
        ((Rec_func_800A9E70_arg0 *)action_state)->unk_8C = 0;
        target_pos = ((S_80175E6C_6_pre *)(((EntityRec *)actor)->target))[-1].unk_00;
        ((EntityRec *)actor)->facing = get_rounded_facing_and_rounding_flag(actor_pos_arg->tile_x,
            actor_pos_arg->tile_y, ((S_80175E6C_5 *)target_pos)->unk_24,
            ((S_80175E6C_5 *)target_pos)->unk_25, &distance);
        actor_pos_arg->frameTable = D_80176348;
        select_sprite_entry(actor_pos_arg, D_80176348[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100)
            >> 9) & 7], 0);
        build_and_display_encoded_message(actor);
        result = 1;
        return result;
    }
    result = 0;
    return result;
}
