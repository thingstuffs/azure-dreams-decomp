#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

extern void select_sprite_entry(void *, u8, s32);
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
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_8014D4D8(void *, void *, void *, void *);
extern void func_8014D71C(void *, void *, void *, void *);
extern s32 func_8014DEC8(void *, void *, void *, void *);
extern void func_8014E08C(void *, void *, void *, void *);
extern s32 func_8014E308(void *, void *, void *, s32);
extern void func_8014FA1C(void *, void *, void *, void *);
extern void func_8014E1A4(void *, void *, void *, void *);

extern u8 D_8014FD30[];
extern u8 D_8014FD38[];
extern u8 D_8014FD68[];
extern u8 D_8014FD70[];
extern u8 D_8014FD78[];

void update_actor_movement_animation_and_facing(ActorActionView *action, EntityRec *motion, ActorSpriteView *sprite, ActorRecord *entity)
{
    u32 initial_flags = g_dungeon_status.flags;
    s16 facing_aux;
    s32 status_flags;
    s8 tile_id;
    s16 facing_angle;
    u16 action_flags;
    u8 *anim_table;
    ActorRecord *player;

    if (initial_flags & 0x1000) {
        action->behavior = 14;
        func_8014D4D8(action, motion, sprite, entity);
        return;
    }

    if (entity->mp == 0) {
        advance_actor_pending_action(action, motion, sprite, entity);
        if (sprite->directionFrames == D_8014FD78) {
            return;
        }
        {
            u8 *early_anim_table = D_8014FD70;
            sprite->directionFrames = early_anim_table;
            select_sprite_entry(
                sprite,
                early_anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (entity->flags1C & 0x200) {
        if (sprite->directionFrames == D_8014FD78) {
            action->behavior = 13;
            action->phase = 1;
            action->nextAction.code = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action, motion, sprite, D_8014FD70) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (entity->flags1C & 0x100) {
            begin_pushed_actor_move(action, motion, sprite, entity);
            return;
        }

        {
            u8 current_state = action->behavior;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_8014FD30;
                if (sprite->directionFrames != anim_table) {
                    sprite->directionFrames = anim_table;
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
            if (begin_ready_actor_directional_action(action, motion, sprite, D_8014FD38) != 0) {
                return;
            }
        }

        if (entity->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(action, motion, sprite, entity);
            func_8014FA1C(action, motion, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(action, motion, sprite, entity);
        }
    }

    tile_id = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->tileIndex.signedIndex = tile_id;

    if (entity->pending_turn_updates > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (sprite->position.packed == ((TilePairView *)&reference_tile_object.tile_position.parts.tile_x)->packed) {
            func_8014D71C(action, motion, sprite, entity);
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
            if ((s16)func_8014E308(action, motion, sprite, 0) == 0) {
                return;
            }
            action_flags = entity->action_flags | 0x4000;
            entity->action_flags = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_8014D71C(action, motion, sprite, entity);
            return;
            }
        }

        switch (entity->action_flags & 0x3FFF) {
        case 8:
            if ((s16)func_8014DEC8(action, motion, sprite, entity) != 0) {
                return;
            }
            func_8014E08C(action, motion, sprite, entity);
            return;
        case 9:
            func_8014E1A4(action, motion, sprite, entity);
            return;
        case 5:
        case 6:
        case 7:
            facing_angle = get_rounded_facing_and_rounding_flag(
                sprite->position.tile.x, sprite->position.tile.y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
            player = primary_actor_record;
            entity->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(action, motion, sprite, D_8014FD68, update_actor_movement_animation_and_facing);
                return;
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(entity);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(action, motion, sprite, D_8014FD68, update_actor_movement_animation_and_facing);
            return;
        default:
            func_8014D71C(action, motion, sprite, entity);
            return;
        }
    }

    status_flags = entity->flags1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_id < 0) ||
            !(dungeon_rooms[tile_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)test_neighbor_position_relation(
                        sprite->position.tile.x, sprite->position.tile.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->position.tile.x, sprite->position.tile.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &facing_aux);
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
    anim_table = D_8014FD30;
    if (sprite->directionFrames == anim_table) {
        return;
    }

    sprite->directionFrames = anim_table;
    select_sprite_entry(
        sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
