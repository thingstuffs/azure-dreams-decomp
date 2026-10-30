#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/nyuel.h"
#include "engine/graphics.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

typedef s32 M2C_UNK;
typedef struct {
    s8 pad_00[0x8C];
    void *unk_8C;
} Actor;
typedef struct {
    u8 pad_00[0x2C];
    u8 *unk_2C;
} Entity;
typedef struct {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} MapObject;

typedef struct S_80170E9C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
} S_80170E9C_0;   /* arg0 in update_entity_actions_facing_and_animation */


s32 check_entity_relation();
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
s32 can_entity_gain_level(void *entity);
void update_actor_status_and_mp(ActorRecord *entity);
void begin_pushed_actor_move(void *state_in, void *unused, void *position_in, void *actor_in);
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
s32 reset_actor_action_state();
extern void func_801737C4(Actor *actor, s32 action, Entity *entity, MapObject *map_object);
s32 complete_timed_tile_movement(void *entity_arg, void *primary_context_arg, void *secondary_context_arg, s32 force_state_arg); /* Unprototyped: this consumer uses the return value, but the owner definition is void. */
extern void func_801747D0(void *entity_data, ObjectPosition *unused_1, s32 unused_2, void *other_data);
extern u8 nyuel_frame_set_2[];
extern u8 nyuel_frame_set_3[];
extern u8 nyuel_frame_set_1[];
extern u8 nyuel_frame_set_12[];
extern u8 nyuel_frame_set_11[];

/* Updates entity actions, facing, and animation from state and terrain. */
/* Selects Nyuel's movement, attacks, spells, and turn processing, dimming its status sprite when its
 * callback is cleared. */
void update_entity_actions_facing_and_animation(ActorRecord *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *state) {
    u16 direction_aux;
    s32 *resume_handler;
    ActorRecord *reference_entity;
    s16 target_angle;
    s32 idle_flags;
    s32 action_id;
    s32 state_flags;
    s8 terrain_index;
    u8 current_mode;
    u16 action_flags;
    u32 idle_mode;

    if (g_dungeon_status.flags & 0x1000) {
        entity->action_id.u = 0xEU;
        func_80171B58(entity, context, sprite, state);
        return;
    }
    if (state->mp_value.parts.whole == 0) {
        advance_actor_pending_action(entity, context, sprite, state);
        if (sprite->frameTable == &nyuel_frame_set_1) {
            return;
        }
        (sprite->frameTable) = &nyuel_frame_set_3;
        select_sprite_entry(sprite, *(u8 *)((((s32)(g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
            >> 9) & 7) + (u32)&nyuel_frame_set_3), 0);
        return;
    }
    state_flags = state->flags1C;
    if (state_flags & 0x200) {
        if (sprite->frameTable == &nyuel_frame_set_1) {
            entity->action_id.u = 0xDU;
            entity->action_phase.s = 1;
            ((S_80170E9C_0 *)entity)->unk_8C = 0;
            state->flags1C = (s32)(state->flags1C & 0xFFFBFFFF);
            sprite->color.c.b = 0x40;
            sprite->color.c.g = 0x40;
            sprite->color.c.r = 0x40;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, &nyuel_frame_set_3) == 0) {
            return;
        }
        state->flags1C |= 0x10000000;
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (state_flags & 0x100) {
            begin_pushed_actor_move(entity, context, sprite, state);
            return;
        }
        current_mode = entity->action_id.u;
        idle_mode = 0xE;
        if (current_mode != idle_mode) {
            if (sprite->frameTable != nyuel_frame_set_2) {
                (sprite->frameTable) = nyuel_frame_set_2;
                select_sprite_entry(sprite, nyuel_frame_set_2[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + state->facing
                    + 0x100) >> 9) & 7], 0);
            }
            entity->action_id.u = idle_mode;
        }
        entity->action_state_flags = (u16)(entity->action_state_flags & 0xFFF3);
        if (state->hp_delta != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, nyuel_frame_set_11) != 0) {
                return;
            }
        }
        if (state->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(entity, context, sprite, state);
            func_801737C4(entity, context, sprite, state);
            return;
        }
        if ((can_entity_gain_level(state) << 0x10) != 0) {
            if ((process_selected_actor_record(entity, context, sprite, state) << 0x10) != 0) {
                func_801747D0(entity, context, sprite, state);
            }
        }
    }
    terrain_index = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = terrain_index;
    if (state->pending_turn_updates > 0) {
        if (state->flags1C & 0x20) {
            update_actor_status_and_mp(state);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            update_actor_movement_and_tile_position(entity, context, sprite, state);
            return;
        }
        if (!(state->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(state, ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((complete_timed_tile_movement(entity, context, sprite, 0) << 0x10) == 0) {
                return;
            }
            action_flags = state->action_flags | 0x4000;
            state->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                update_actor_movement_and_tile_position(entity, context, sprite, state);
                return;
            }
        }
        action_id = state->action_flags & 0x3FFF;
        switch (action_id) {
        case 8:
        case 9:
            if ((check_movement_and_initialize_action(entity, context, sprite, state) << 0x10) != 0) {
                return;
            }
            start_directional_animation_if_allowed(entity, context, sprite, state);
            return;
        case 5:
        case 6:
        case 7:
            target_angle = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            reference_entity = primary_actor_record;
            state->facing = target_angle;
            if (reference_entity->action_id.u == 0x11) {
                resume_handler = (s32 *)update_entity_actions_facing_and_animation;
                begin_actor_spell_action(entity, context, sprite, &nyuel_frame_set_12, resume_handler);
                return;
            }
        case 12:
            update_actor_status_and_mp(state);
            return;
        case 1:
        case 2:
        case 3:
            resume_handler = (s32 *)update_entity_actions_facing_and_animation;
            begin_actor_spell_action(entity, context, sprite, &nyuel_frame_set_12, resume_handler);
            return;
        case 11:
        default:
            update_actor_movement_and_tile_position(entity, context, sprite, state);
            return;
        }
    }
    idle_flags = state->flags1C;
    if (!(idle_flags & 0x2000)) {
        if (terrain_index < 0 || !(dungeon_rooms[terrain_index].flags & 2)) {
            if (!(idle_flags & 0x430)) {
                if ((test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
                    state->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x,
                        sprite->tile_y, reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
                }
            }
        }
    }
block_59:
    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    if (sprite->frameTable == (void *)nyuel_frame_set_2) {
        return;
    }
    (sprite->frameTable) = (void *)nyuel_frame_set_2;
    select_sprite_entry(sprite, nyuel_frame_set_2[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
        >> 9) & 7], 0);
    return;
}
