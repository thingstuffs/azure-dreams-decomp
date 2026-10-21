#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* The action record shares its timer bytes between signed tests and unsigned updates. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    void *nextBehavior;
    s32 scratch;
    u8 pad_94[2];
    union { u16 raw; s16 signedValue; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[2];
    s16 idleElapsed;
    s16 idleDelay;
    u8 pad_A2[0xA];
    union { u16 raw; s16 signedValue; } startHeight;
} ActorActionView;

/* Sprite state passed to the frame selector; the tile pair is also compared as one halfword. */
typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 framePhase;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[6];
    u16 scaleX;
    u16 scaleY;
    u8 pad_20[4];
    union { struct { u8 x, y; } bytes; u16 packed; } tile;
    union { u8 raw; s8 signedValue; } room;
    u8 pad_27[5];
    u8 *frameTable;
} ActorSpriteView;

extern void select_sprite_entry();
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 test_neighbor_position_relation(u8, u8, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, ActorSpriteView *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8016C24C(void *, void *, void *, void *);
extern void func_8016C490(void *, void *, void *, void *);
extern s32 func_8016CC44(void *, void *, void *, void *);
extern void func_8016CE08(void *, void *, void *, void *);
extern s32 func_8016CF20(void *, void *, void *, s32);
extern void func_8016E650(void *, void *, void *, void *);
extern void func_8016E824(void *, void *, void *, void *);

extern u8 D_8016EEB8[];
extern u8 D_8016EEC0[];
extern u8 D_8016EEF0[];
extern u8 D_8016EEF8[];
extern u8 D_8016EF00[];

/* Updates an actor's dungeon behavior, facing, and animation. */
void update_actor_dungeon_behavior(ActorActionView *action, void *context, ActorSpriteView *sprite, ActorRecord *entity)
{
    u32 initial_flags = g_dungeon_status.flags;
    s16 distance;
    s32 status_flags;
    s8 room_id;
    s16 facing;
    u16 action_flags;
    u8 *anim_table;
    ActorRecord *player;

    if (initial_flags & 0x1000) {
        action->behavior = 14;
        func_8016C24C(action, context, sprite, entity);
        return;
    }

    if (entity->mp == 0) {
        advance_actor_pending_action(action, context, sprite, entity);
        if (sprite->frameTable == D_8016EF00) {
            return;
        }
        {
            u8 *early_anim_table = D_8016EEF8;
            (sprite->frameTable) = early_anim_table;
            select_sprite_entry(
                sprite,
                early_anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (entity->flags1C & 0x200) {
        if (sprite->frameTable == D_8016EF00) {
            action->behavior = 13;
            action->phase = 1;
            action->nextBehavior = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action, context, sprite, D_8016EEF8) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (entity->flags1C & 0x100) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        {
            u8 current_state = action->behavior;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_8016EEB8;
                if (sprite->frameTable != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(
                        sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                }
                action->behavior = next_state;
            }
        }

        action->flags &= 0xFFF3;

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, context, sprite, D_8016EEC0) != 0) {
                    return;
            }
        }

        if (entity->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            func_8016E650(action, context, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(action, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile.bytes.x, sprite->tile.bytes.y);
    sprite->room.signedValue = room_id;

    if (entity->pending_turn_updates > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (sprite->tile.packed == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8016C490(action, context, sprite, entity);
            return;
        }
        action_flags = entity->action_flags;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        entity, (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_8016CF20(action, context, sprite, 0) == 0) {
                    return;
            }
            action_flags = entity->action_flags | 0x4000;
            entity->action_flags = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8016C490(action, context, sprite, entity);
                return;
            }
        }

        switch (entity->action_flags & 0x3FFF) {
        case 8:
            if ((s16)func_8016CC44(action, context, sprite, entity) != 0) {
                    return;
            }
            func_8016CE08(action, context, sprite, entity);
            return;
        case 9:
            func_8016E824(action, context, sprite, entity);
            return;
        case 5:
        case 6:
        case 7:
            facing = get_rounded_facing_and_rounding_flag(
                sprite->tile.bytes.x, sprite->tile.bytes.y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            player = primary_actor_record;
            entity->facing = facing;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(action, context, sprite, D_8016EEF0, update_actor_dungeon_behavior);
                    return;
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(entity);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(action, context, sprite, D_8016EEF0, update_actor_dungeon_behavior);
            return;
        default:
            func_8016C490(action, context, sprite, entity);
            return;
        }
    }

    status_flags = entity->flags1C;
    if (!(status_flags & 0x2000)) {
        if ((room_id < 0) ||
            !(dungeon_rooms[room_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)test_neighbor_position_relation(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
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
    anim_table = D_8016EEB8;
    if (sprite->frameTable == anim_table) {
        return;
    }

    (sprite->frameTable) = anim_table;
    select_sprite_entry(
        sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
