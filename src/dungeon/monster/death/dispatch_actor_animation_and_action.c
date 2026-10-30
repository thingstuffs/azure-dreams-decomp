#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
void advance_entity_path_state(ActorRecord *motion_state, ObjectPosition *unused, SpriteFrameState *entity, ActorRecord *path_state);
extern void func_801721D8(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
s32 attempt_target_action(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *target, ActorRecord *actor);
void apply_conditional_actor_effect(ActorRecord *action_state, ObjectPosition *effect_context, SpriteFrameState *action_context, ActorRecord *actor);
extern s32 func_80172B8C(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern s32 death_action_resume_address;
extern u8 death_direction_frames[];
extern u8 death_frame_set_7[];
extern u8 death_frame_set_8[];
extern u8 death_frame_set_1[];
extern u8 death_frame_set_2[];

typedef struct S_801719DC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    s16 unk_B8;
} S_801719DC_0;   /* arg0 in dispatch_actor_animation_and_action */

typedef struct S_801719DC_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_801719DC_1;   /* arg3 in dispatch_actor_animation_and_action */

/* Update actor animation, facing, and action dispatch from dungeon state. */
/* Dispatches Death's movement, attacks, spells, and turn processing, resetting its vertical animation
 * offsets on return to idle. */
void dispatch_actor_animation_and_action(ActorRecord *motion_in, ObjectPosition *context_in, SpriteFrameState *entity_in, ActorRecord *actor_in) {
    u16 direction_aux;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        motion_in->action_id.u = 0xE;
        advance_entity_path_state(motion_in, context_in, entity_in, actor_in);
        return;
    }
    if (actor_in->mp_value.parts.whole == 0) {
        void *anim_table;

        advance_actor_pending_action(motion_in, context_in, entity_in, actor_in);
        if (entity_in->frameTable == death_frame_set_2) {
            return;
        }
        anim_table = death_frame_set_1;
        (entity_in->frameTable) = anim_table;
        select_sprite_entry(entity_in,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_801719DC_1 *)actor_in)->unk_1C & 0x200) {
        if (entity_in->frameTable == death_frame_set_2) {
            motion_in->action_id.u = 0xD;
            motion_in->action_phase.u = 1;
            ((S_801719DC_0 *)motion_in)->unk_8C = 0;
            ((S_801719DC_1 *)actor_in)->unk_1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(motion_in, context_in, entity_in, death_frame_set_1) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_801719DC_1 *)actor_in)->unk_1C & 0x100) {
            begin_pushed_actor_move(motion_in, context_in, entity_in, actor_in);
            return;
        }

        {
            s32 current_state;
            u32 next_state;
            void *current_anim;
            void *anim_table;
            s32 motion_value;

            current_state = motion_in->action_id.u;

            next_state = 0xE;
            if (current_state != next_state) {
                current_anim = entity_in->frameTable;
                anim_table = death_direction_frames;
                if (current_anim != anim_table) {
                    (entity_in->frameTable) = anim_table;
                    select_sprite_entry(entity_in,
                        ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100)
                            >> 9) & 7],
                        1);
                    entity_in->frame_ticks = 1;
                    motion_value = motion_in->unk_A4.value;
                    ((S_801719DC_0 *)motion_in)->unk_A4.at02.v = 0;
                    ((S_801719DC_0 *)motion_in)->unk_B8 = 0;
                    ((S_801719DC_0 *)motion_in)->unk_AC = 0;
                    ((S_801719DC_0 *)motion_in)->unk_B0 = 0;
                    ((S_801719DC_0 *)motion_in)->unk_A8 = motion_value;
                }
                motion_in->action_id.u = next_state;
            }
        }

        motion_in->action_state_flags &= 0xFFF3;
        ((S_801719DC_1 *)actor_in)->unk_1C |= 0x40000;

        if (actor_in->hp_delta != 0) {
            if (begin_ready_actor_directional_action(motion_in, context_in, entity_in, death_frame_set_7) != 0) {
                return;
            }
        }

        if (((S_801719DC_1 *)actor_in)->unk_1C & 0x80000) {
            u16 base_offset;
            u16 offset_delta;
            s32 motion_value;

            begin_actor_move_to_target_facing(motion_in, context_in, entity_in, actor_in);
            base_offset = motion_in->unk_90.parts.high.u;
            offset_delta = ((S_801719DC_0 *)motion_in)->unk_A4.at02u.v;
            motion_value = motion_in->unk_A4.value;
            ((S_801719DC_0 *)motion_in)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)motion_in)->unk_B8 = 0;
            ((S_801719DC_0 *)motion_in)->unk_AC = 0;
            ((S_801719DC_0 *)motion_in)->unk_B0 = 0;
            motion_in->unk_90.parts.high.u = base_offset - offset_delta;
            ((S_801719DC_0 *)motion_in)->unk_A8 = motion_value;
            func_801743F0(motion_in, context_in, entity_in, actor_in);
            return;
        }

        if ((can_entity_gain_level(actor_in) << 16) != 0) {
            process_selected_actor_record(motion_in, context_in, entity_in, actor_in);
        }
    }

    room_id = find_active_rect_containing_point(entity_in->tile_x, entity_in->tile_y);
    entity_in->room_index = room_id;

    if (actor_in->pending_turn_updates > 0) {
        if (((S_801719DC_1 *)actor_in)->unk_1C & 0x20) {
            update_actor_status_and_mp(actor_in);
            return;
        }
        if (*(u16 *)&entity_in->tile_x == reference_tile_object.tile_position.word) {
            func_801721D8(motion_in, context_in, entity_in, actor_in);
            return;
        }
        if (!(actor_in->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor_in,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((func_80172B8C(motion_in, context_in, entity_in, 0) << 16) == 0) {
                return;
            }
            action_state = actor_in->action_flags | 0x4000;
            actor_in->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                func_801721D8(motion_in, context_in, entity_in, actor_in);
                return;
            }
        }

        action_state = actor_in->action_flags & 0x3FFF;
        switch (action_state - 1) {

        case 7:
        case 8:
            if ((attempt_target_action(motion_in, context_in, entity_in, actor_in) << 16) != 0) {
                return;
            }
            apply_conditional_actor_effect(motion_in, context_in, entity_in, actor_in);
            return;

        case 4:
        case 5:
        case 6:
        {
            ActorRecord *player;
            s16 heading;

            heading = get_rounded_facing_and_rounding_flag(
                entity_in->tile_x, entity_in->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                &direction_aux);
            player = primary_actor_record;
            actor_in->facing = heading;
            if (player->action_id.u == 0x11) {
                begin_actor_spell_action(motion_in, context_in, entity_in, death_frame_set_8, &death_action_resume_address);
                return;
            }
        }

        case 11:
            update_actor_status_and_mp(actor_in);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(motion_in, context_in, entity_in, death_frame_set_8, &death_action_resume_address);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_801721D8(motion_in, context_in, entity_in, actor_in);
            return;
        }
    }

    if (!(((S_801719DC_1 *)actor_in)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((S_801719DC_1 *)actor_in)->unk_1C & 0x430)) {

                if ((test_neighbor_position_relation(
                        entity_in->tile_x, entity_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    actor_in->facing = get_rounded_facing_and_rounding_flag(
                        entity_in->tile_x, entity_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (entity_in->flags & 0x40) {
        return;
    }
    {
        void *anim_table = death_direction_frames;
        s32 motion_value;

        if (entity_in->frameTable != anim_table) {
            (entity_in->frameTable) = anim_table;
            select_sprite_entry(entity_in,
                ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor_in->facing + 0x100) >> 9) & 7],
                1);
            entity_in->frame_ticks = 1;
            motion_value = motion_in->unk_A4.value;
            ((S_801719DC_0 *)motion_in)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)motion_in)->unk_B8 = 0;
            ((S_801719DC_0 *)motion_in)->unk_AC = 0;
            ((S_801719DC_0 *)motion_in)->unk_B0 = 0;
            ((S_801719DC_0 *)motion_in)->unk_A8 = motion_value;
        }
    }
}
