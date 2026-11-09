#include "shared/actor_status_flags.h"
#include "common.h"
#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/actor.h"
#include "dungeon/monster/pulunpa.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"
#include "records/Rec_func_800A5DFC_arg1.h"
#include "dungeon/actor/status.h"
#include "dungeon/player/object.h"
#include "dungeon/actor/spell_resource_ids_g01008.h"
#include "dungeon/item.h"
#include "dungeon/system.h"
#include "sdk/libgte.h"



extern u8 pulunpa_action_resume_address[];
extern u8 D_801762D8[];
extern u8 D_801762E0[];

/* Animate a hop to the actor's tile and finish the action when its timer expires. */
void animate_hop_to_actor_tile(ActorRecord *action, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 target_distance;
    s32 tile_origin_y;
    s32 hop_frames;
    s32 next_hop_frame;
    s32 actor_flags;
    u16 action_timer;
    s32 phase;

    phase = action->action_phase;
    switch (phase) {
    case 0:
        if (sprite->flags & 0x6000) {
            sprite->frameTable = D_801762D8;
            select_sprite_entry(
                sprite,
                D_801762D8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >>
                            9) &
                           7],
                0);
            action->action_state_flags |= 8;
            actor->flags1C &= ACTOR_GROUNDED_CLEAR_MASK;
            action->unk_9E = 5;
            action->unk_A0.value = 0;
            action->action_phase++;
        } else {
            break;
        }
                        /* fallthrough */

    case 1:
        hop_frames = action->unk_9E;
        action->unk_90.value =
            action->unk_90.value - action->unk_A0.value;
        if (hop_frames != 0) {
            motion->velocity_x =
                (((sprite->tile_x << 6) -
                  ({ motion->x.w.i - 0x20; })) <<
                 0x10) /
                hop_frames;
            motion->velocity_y =
                (((sprite->tile_y << 6) -
                  (tile_origin_y = motion->y.w.i - 0x20)) <<
                 0x10) /
                action->unk_9E;
            action->unk_A0.value =
                (-rsin(action->unk_9E * 0x199)) << 9;
        }
        action->unk_90.value =
            action->unk_90.value + action->unk_A0.value;
        next_hop_frame = (u16)action->unk_9E - 1;
        action->unk_9E = next_hop_frame;
        if ((s16)next_hop_frame < 0) {
            action->unk_90.value = 0;
            action->action_state_flags &= 0xFFF7;
            actor->flags1C |= ACTOR_GROUNDED;
            action->action_phase++;
        }

                        /* fallthrough */

    case 2:
        if (actor->flags1C & ACTOR_GROUNDED) {
            action->action_state_flags &= 0xFFF7;
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, sprite->tile_x,
                          sprite->tile_y);
            sprite->frameTable = D_801762E0;
            select_sprite_entry(
                sprite,
                D_801762E0[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >>
                            9) &
                           7],
                0);
            action->action_phase++;
        }

    }

    action_timer = action->action_timer - 1;
    action->action_timer = action_timer;
    if ((action_timer << 0x10) <= 0) {
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, sprite->tile_x,
                      sprite->tile_y);
        spend_actor_mp(actor, 4);
        advance_status_timers(actor);
        if (g_dungeon_status.activity_counts.parts.pending_movement_count != 0) {
            g_dungeon_status.activity_counts.parts.pending_movement_count = (u16)g_dungeon_status.activity_counts.parts.pending_movement_count - 1;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x2000) {
            u16 status_flags;

            status_flags = actor->action_flags;
            if (status_flags & 0x8000) {
                actor->action_flags = status_flags & 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {
                actor->facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &target_distance);
            }
        }
        apply_capped_damage_and_hit_effect(actor, motion);
        if ((check_actor_floor_trap(sprite, actor) << 0x10) > 0) {
            action->unk_8C.address = pulunpa_action_resume_address;
            on_actor_status_updated(actor);
        }
    }
}
