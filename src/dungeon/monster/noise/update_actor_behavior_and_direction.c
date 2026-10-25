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
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_80171CD8(void *, void *, void *, void *);
extern void update_actor_turn_behavior(void *, void *, void *, void *);
extern s32 func_801726D0(void *, void *, void *, void *);
extern void func_80172894(void *, void *, void *, void *);
extern s32 func_801729AC(void *, void *, void *, s32);
extern void func_80174598(void *, void *, void *, void *);
extern void start_directional_action_and_record_tile(void *, void *, void *, void *);

extern u8 noise_ability_resume_address[];
extern u8 noise_direction_frames[];
extern u8 D_80174E98[];
extern u8 noise_spell_frame_set[];
extern u8 noise_frame_set_3[];
extern u8 noise_frame_set[];

/* Update the actor's dungeon behavior, facing, and directional animation. */
void update_actor_behavior_and_direction(void *motion, void *render_ctx, SpriteFrameState *map_entity, ActorRecord *actor)
{
    u8 *anim_table;
    s32 room_id;
    u16 direction_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = 0xE;
        func_80171CD8(motion, render_ctx, map_entity, actor);
        return;
    }

    if (actor->mp == 0) {
        advance_actor_pending_action(motion, render_ctx, map_entity, actor);
        if (map_entity->frameTable != noise_frame_set) {
            (map_entity->frameTable) = noise_frame_set_3;
            select_sprite_entry(map_entity,
                *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)noise_frame_set_3),
                0);
            return;
        }
        return;
    }

    if (((u32)actor->flags1C) & ACTOR_ASLEEP) {
        if (map_entity->frameTable == noise_frame_set) {
            ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)motion)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)motion)->unk_8C = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(motion, render_ctx, map_entity, noise_frame_set_3)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(motion, render_ctx, map_entity, actor);
            return;
        }

        {
            u8 current_state;
            u8 idle_state;

            current_state = *(u8 *)((u8 *)motion + 0x9A);
            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = noise_direction_frames;
                if (map_entity->frameTable != anim_table) {
                    (map_entity->frameTable) = anim_table;
                    select_sprite_entry(map_entity,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)motion)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)motion)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
                ((Rec_func_800A9E70_arg0 *)motion)->unk_9A.as_u8 = idle_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)motion)->unk_98 &= 0xFFF3;
        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(motion, render_ctx, map_entity, D_80174E98)) {
                return;
            }
        }

        if (((u32)actor->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(motion, render_ctx, map_entity, actor);
            func_80174598(motion, render_ctx, map_entity, actor);
            return;
        }

        if ((can_entity_gain_level(actor) << 16) != 0) {
            process_selected_actor_record(motion, render_ctx, map_entity, actor);
        }
    }

    room_id = find_active_rect_containing_point(map_entity->tile_x, map_entity->tile_y);
    map_entity->room_index = room_id;

    if (actor->pending_turn_updates > 0) {
        u16 action_state;

        if (((u32)actor->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (!( *(u16 *)&map_entity->tile_x ==reference_tile_object.tile_position.word)) {
            if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(actor,
                            (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801729AC(motion, render_ctx, map_entity, 0) << 16) == 0) {
                    return;
                }
                action_state = actor->action_flags | 0x4000;
                actor->action_flags = action_state;
            }

            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                action_state = actor->action_flags & ACTOR_ACTION_CODE_MASK;
                switch (action_state) {
                case 8:
                    if ((func_801726D0(motion, render_ctx, map_entity, actor) << 16) != 0) {
                        return;
                    }
                    func_80172894(motion, render_ctx, map_entity, actor);
                    return;

                case 9:
                    start_directional_action_and_record_tile(motion, render_ctx, map_entity, actor);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    ActorRecord *player;
                    s16 facing_angle;

                    facing_angle = get_rounded_facing_and_rounding_flag(
                        map_entity->tile_x, map_entity->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_flags);
                    player = primary_actor_record;
                    actor->facing = facing_angle;
                    if (player->action_id == 0x11) {
                        begin_actor_spell_action(motion, render_ctx, map_entity, noise_spell_frame_set, noise_ability_resume_address);
                        return;
                    }
                }

                case 12:
                    update_actor_status_and_mp(actor);
                    return;

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(motion, render_ctx, map_entity, noise_spell_frame_set, noise_ability_resume_address);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }
        update_actor_turn_behavior(motion, render_ctx, map_entity, actor);
        return;
    } else if (!(((u32)actor->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        map_entity->tile_x, map_entity->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
                        map_entity->tile_x, map_entity->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_flags);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (map_entity->flags & 0x40) {
        return;
    }
    anim_table = noise_direction_frames;
    if (map_entity->frameTable == anim_table) {
        return;
    }
    (map_entity->frameTable) = anim_table;
    select_sprite_entry(map_entity,
        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
