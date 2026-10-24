#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/monster/nyuel.h"

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

typedef struct S_80170E9C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
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
} S_80170E9C_1;   /* arg3 in update_entity_actions_facing_and_animation */

void select_sprite_entry();
s32 check_entity_relation();
s8 find_active_rect_containing_point();
s32 test_neighbor_position_relation();
s16 get_rounded_facing_and_rounding_flag();
s32 can_entity_gain_level();
void update_actor_status_and_mp();
void begin_pushed_actor_move();
s32 begin_ready_actor_directional_action();
s32 advance_actor_pending_action();
void begin_actor_move_to_target_facing();
s32 reset_actor_action_state();
s32 process_selected_actor_record();
void begin_actor_spell_action();
extern void func_80171B58(void *);
extern void func_801737C4(Actor *actor, s32 action, Entity *entity, MapObject *map_object);
s32 complete_timed_tile_movement();
extern void func_801747D0(void *entity_data, s32 unused_1, s32 unused_2, void *other_data);
extern u8 nyuel_frame_set_2[];
extern u8 nyuel_frame_set_3[];
extern u8 nyuel_frame_set_1[];
extern u8 nyuel_frame_set_12[];
extern u8 nyuel_frame_set_11[];

/* Updates entity actions, facing, and animation from state and terrain. */
/* Selects Nyuel's movement, attacks, spells, and turn processing, dimming its status sprite when its
 * callback is cleared. */
void update_entity_actions_facing_and_animation(void *entity, s32 context, SpriteFrameState *sprite, void *state) {
    s32 direction_aux;
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
        ((S_80170E9C_0 *)entity)->unk_9A = 0xEU;
        func_80171B58(entity);
        return;
    }
    if (((S_80170E9C_1 *)state)->unk_25 == 0) {
        advance_actor_pending_action(entity, context, sprite, state);
        if (sprite->frameTable == &nyuel_frame_set_1) {
            return;
        }
        (sprite->frameTable) = &nyuel_frame_set_3;
        select_sprite_entry(sprite, *(u8 *)((((s32)(g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170E9C_1 *)state)->unk_2A + 0x100)
            >> 9) & 7) + (u32)&nyuel_frame_set_3), 0);
        return;
    }
    state_flags = ((S_80170E9C_1 *)state)->unk_1C;
    if (state_flags & 0x200) {
        if (sprite->frameTable == &nyuel_frame_set_1) {
            ((S_80170E9C_0 *)entity)->unk_9A = 0xDU;
            ((S_80170E9C_0 *)entity)->unk_9B = 1;
            ((S_80170E9C_0 *)entity)->unk_8C = 0;
            ((S_80170E9C_1 *)state)->unk_1C = (s32)(((S_80170E9C_1 *)state)->unk_1C & 0xFFFBFFFF);
            sprite->color.c.b = 0x40;
            sprite->color.c.g = 0x40;
            sprite->color.c.r = 0x40;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, &nyuel_frame_set_3) == 0) {
            return;
        }
        ((S_80170E9C_1 *)state)->unk_1C |= 0x10000000;
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (state_flags & 0x100) {
            begin_pushed_actor_move(entity, context, sprite, state);
            return;
        }
        current_mode = ((S_80170E9C_0 *)entity)->unk_9A;
        idle_mode = 0xE;
        if (current_mode != idle_mode) {
            if (sprite->frameTable != nyuel_frame_set_2) {
                (sprite->frameTable) = nyuel_frame_set_2;
                select_sprite_entry(sprite, nyuel_frame_set_2[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170E9C_1 *)state)->unk_2A
                    + 0x100) >> 9) & 7], 0);
            }
            ((S_80170E9C_0 *)entity)->unk_9A = idle_mode;
        }
        ((S_80170E9C_0 *)entity)->unk_98 = (u16)(((S_80170E9C_0 *)entity)->unk_98 & 0xFFF3);
        if (((S_80170E9C_1 *)state)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, &nyuel_frame_set_11) != 0) {
                return;
            }
        }
        if (((S_80170E9C_1 *)state)->unk_1C & 0x80000) {
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
    if (((S_80170E9C_1 *)state)->unk_6D > 0) {
        if (((S_80170E9C_1 *)state)->unk_1C & 0x20) {
            update_actor_status_and_mp(state);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            update_actor_movement_and_tile_position(entity, context, sprite, state);
            return;
        }
        if (!(((S_80170E9C_1 *)state)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(state, ((s32)primary_actor_record->previous_actor_header) + 0x20) << 0x10) != 0) {
                    return;
                }
            }
            if ((complete_timed_tile_movement(entity, context, sprite, 0) << 0x10) == 0) {
                return;
            }
            action_flags = ((S_80170E9C_1 *)state)->unk_46 | 0x4000;
            ((S_80170E9C_1 *)state)->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                update_actor_movement_and_tile_position(entity, context, sprite, state);
                return;
            }
        }
        action_id = ((S_80170E9C_1 *)state)->unk_46 & 0x3FFF;
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
            ((S_80170E9C_1 *)state)->unk_2A = target_angle;
            if (reference_entity->action_id == 0x11) {
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
    idle_flags = ((S_80170E9C_1 *)state)->unk_1C;
    if (!(idle_flags & 0x2000)) {
        if (terrain_index < 0 || !(dungeon_rooms[terrain_index].flags & 2)) {
            if (!(idle_flags & 0x430)) {
                if ((test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 0x10) != 0) {
                    ((S_80170E9C_1 *)state)->unk_2A = get_rounded_facing_and_rounding_flag(sprite->tile_x,
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
    select_sprite_entry(sprite, nyuel_frame_set_2[((s32)(g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170E9C_1 *)state)->unk_2A + 0x100)
        >> 9) & 7], 0);
    return;
}
