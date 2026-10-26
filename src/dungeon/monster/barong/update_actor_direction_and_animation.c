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
extern s32 rand(void);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, u8 *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, void * unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, void * effect_param, void *target, u8 *direction_table, void * next_state);
extern void func_80171CA8(void *, void *, void *, void *);
extern void func_80171EEC(void *, void *, void *, void *);
extern s32 func_801726B0(void *, void *, void *, void *);
extern void update_boss_effect_growth(void *, void *, void *, void *);
extern s32 func_8017298C(void *, void *, void *, s32);
extern void func_8017430C(void *, void *, void *, void *);
extern void start_direction_based_action(void *, void *, void *, void *);

extern u8 barong_action_resume_address[];
#include "dungeon/monster/barong.h"
extern u8 barong_frame_set_1[];
extern u8 barong_frame_set_4[];
extern u8 barong_frame_set[];
extern u8 barong_frame_set_5[];
extern u8 barong_frame_set_2[];

/* Updates a dungeon actor's behavior, facing, and directional animation. */
void update_actor_direction_and_animation(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite, ActorRecord *entity_arg) {
    u8 *anim_table;
    s32 room_id;
    u16 distance;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171CA8(actor_arg, context_arg, sprite, entity_arg);
        return;
    }

    if (entity_arg->mp == 0) {
        advance_actor_pending_action(actor_arg, context_arg, sprite, entity_arg);
        {
        void *current_anim = sprite->frameTable;
        sprite->frameTable = current_anim;
        if (current_anim != barong_frame_set_2) {
            (sprite->frameTable) = barong_frame_set_5;
            {
                s32 direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite, barong_frame_set_5[direction_index], 0);
            }
        }
        }
        return;
    }

    if (((u32)entity_arg->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == barong_frame_set_2) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            entity_arg->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, sprite, barong_frame_set_5)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity_arg->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor_arg, context_arg, sprite, entity_arg);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 != 0xE) {
            u8 idle_state = 0xE;

            anim_table = barong_direction_frames;
            if (sprite->frameTable != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9E.as_s16 = 0;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = idle_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;
        if (entity_arg->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, sprite, barong_frame_set_4)) {
                return;
            }
        }

        if (((u32)entity_arg->flags1C) & ACTOR_LIFTED) {
            u8 *event_table;
            u8 *anim_entry;
            void *anim_sprite;
            s32 direction_index;

            begin_actor_move_to_target_facing(actor_arg, context_arg, sprite, entity_arg);
            func_8017430C(actor_arg, context_arg, sprite, entity_arg);
            event_table = barong_frame_set_1;
            (sprite->frameTable) = event_table;
            direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7;
            anim_sprite = sprite;
            anim_entry = event_table + direction_index;
            select_sprite_entry(anim_sprite, anim_entry[0], 0);
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((can_entity_gain_level(entity_arg) << 16) != 0) {
            process_selected_actor_record(actor_arg, context_arg, sprite, entity_arg);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (entity_arg->pending_turn_updates > 0) {
        u16 action_flags;

        if (((u32)entity_arg->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity_arg);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_80171EEC(actor_arg, context_arg, sprite, entity_arg);
            return;
        }
        if (!(entity_arg->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity_arg,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017298C(actor_arg, context_arg, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = entity_arg->action_flags | 0x4000;
            entity_arg->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                func_80171EEC(actor_arg, context_arg, sprite, entity_arg);
                return;
            }
        }

        action_flags = entity_arg->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_flags) {
        case 8:
            if ((func_801726B0(actor_arg, context_arg, sprite, entity_arg) << 16) != 0) {
                return;
            }
            update_boss_effect_growth(actor_arg, context_arg, sprite, entity_arg);
            return;

        case 9:
            start_direction_based_action(actor_arg, context_arg, sprite, entity_arg);
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
            entity_arg->facing = heading;
            if (player->action_id == 0x11) {
                begin_actor_spell_action(actor_arg, context_arg, sprite, barong_frame_set, barong_action_resume_address);
                return;
            }
        }

        case 12:
            update_actor_status_and_mp(entity_arg);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_arg, context_arg, sprite, barong_frame_set, barong_action_resume_address);
            return;

        default:
            func_80171EEC(actor_arg, context_arg, sprite, entity_arg);
            return;
        }
    } else if (!(((u32)entity_arg->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)entity_arg->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity_arg->facing = get_rounded_facing_and_rounding_flag(
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
    anim_table = barong_direction_frames;
    if (sprite->frameTable == anim_table) {
        return;
    }
    (sprite->frameTable) = anim_table;
    {
        s32 direction_index = ((g_game_work.view.camera_rotation.parts.viewAngle + entity_arg->facing + 0x100) >> 9) & 7;
        select_sprite_entry(sprite, anim_table[direction_index], 0);
    }
}
