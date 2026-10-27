#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void * unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void * effect_param, void *target, u8 *direction_table, void * next_state);
extern void advance_entity_along_stored_path(void *, void *, void *, void *);
extern void func_80171F40(void *, void *, void *, void *);
extern s32 func_80172710(void *, void *, void *, void *);
extern void func_801728D4(void *, void *, void *, void *);
extern s32 func_801729EC(void *, void *, void *, s32);
extern void update_timed_effect_size_and_position(void *, void *, void *, void *);
void clear_actor_flag_and_apply_effect(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *anim_state, ActorRecord *actor);

#include "dungeon/monster/saber.h"

extern u8 saber_frame_set_10[];
extern u8 saber_frame_set_2[];
extern u8 saber_frame_set_11[];


/* Updates creature behavior, facing, and animation from dungeon and action state. */
void update_creature_behavior_and_animation_2(ActorRecord *actor_in, ObjectPosition *context_in, SpriteFrameState *sprite, ActorRecord *creature_in) {
    u8 *anim_table;
    u16 distance;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = 0xE;
        advance_entity_along_stored_path(actor_in, context_in, sprite, creature_in);
        return;
    }

    if (creature_in->mp == 0) {
        advance_actor_pending_action(actor_in, context_in, sprite, creature_in);
        if (sprite->frameTable == saber_direction_frames_2) {
            return;
        }
        (sprite->frameTable) = saber_frame_set_11;
        select_sprite_entry(sprite,
            saber_frame_set_11[((g_game_work.view.camera_rotation.parts.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature_in->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == saber_direction_frames_2) {
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_8C = 0;
            creature_in->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor_in, context_in, sprite, saber_frame_set_11) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature_in->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor_in, context_in, sprite, creature_in);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = saber_direction_frames;
                if (sprite->frameTable != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor_in)->unk_98 &= 0xFFF3;
        if (creature_in->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_in, context_in, sprite, saber_frame_set_10) != 0) {
                return;
            }
        }

        if (((u32)creature_in->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor_in, context_in, sprite, creature_in);
            update_timed_effect_size_and_position(actor_in, context_in, sprite, creature_in);
            (sprite->frameTable) = saber_direction_frames;
            select_sprite_entry(sprite,
                saber_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((can_entity_gain_level(creature_in) << 16) != 0) {
            process_selected_actor_record(actor_in, context_in, sprite, creature_in);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (creature_in->pending_turn_updates > 0) {
        if (((u32)creature_in->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(creature_in);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_80171F40(actor_in, context_in, sprite, creature_in);
            return;
        }
        if (!(creature_in->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature_in,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801729EC(actor_in, context_in, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature_in->action_flags | 0x4000;
            creature_in->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                func_80171F40(actor_in, context_in, sprite, creature_in);
                return;
            }
        }

        action_flags = creature_in->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_flags) {
        case 8:
            if ((func_80172710(actor_in, context_in, sprite, creature_in) << 16) != 0) {
                return;
            }
            func_801728D4(actor_in, context_in, sprite, creature_in);
            return;

        case 9:
            clear_actor_flag_and_apply_effect(actor_in, context_in, sprite, creature_in);
            return;

        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                creature_in->facing = heading;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor_in, context_in, sprite, saber_frame_set_2, &saber_behavior_entry);
                    return;
                }
            }

        case 12:
            update_actor_status_and_mp(creature_in);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_in, context_in, sprite, saber_frame_set_2, &saber_behavior_entry);
            return;

        case 10:
        default:
            func_80171F40(actor_in, context_in, sprite, creature_in);
            return;
        }
    }

    if (!(((u32)creature_in->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)creature_in->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    creature_in->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    anim_table = saber_direction_frames;
    if (sprite->frameTable == anim_table) {
        return;
    }
    (sprite->frameTable) = anim_table;
    select_sprite_entry(sprite,
        *(u8 *)(((((g_game_work.view.camera_rotation.parts.viewAngle + creature_in->facing + 0x100) >> 9) & 7)) + (u32)anim_table),
        0);
}
