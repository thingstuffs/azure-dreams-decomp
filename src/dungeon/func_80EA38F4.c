#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

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

extern void select_sprite_entry();
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(ActorActionView *action, s32 unused, ActorSpriteView *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(ActorActionView *action, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_80159684(void *, void *, void *, void *);
extern void func_801598DC(void *, void *, void *, void *);
extern s32 func_8015A088(void *, void *, void *, void *);
extern void func_8015A24C(void *, void *, void *, void *);
extern s32 func_8015A364(void *, void *, void *, s32);
extern void func_8015C060(void *, void *, void *, void *);
extern void func_8015C234(void *, void *, void *, void *);
extern void func_8015CB14(void *, void *, void *, void *);

extern u8 D_800DCF5B;
extern u8 D_8015CF00[];
extern u8 D_8015CF08[];
extern u8 D_8015CF38;
extern u8 D_8015CF40;
extern u8 D_8015CF48;

/* Updates dungeon action behavior, facing, and animation from its current state. */
void update_dungeon_action_behavior_facing_animation_state(ActorActionView *action, void *context, ActorSpriteView *sprite, ActorRecord *entity)
{
    u8 *anim_table;
    s32 direction_flags;
    s8 room_id;
    u16 action_state;
    u16 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        action->behavior = 0xE;
        func_80159684(action, context, sprite, entity);
        return;
    }

    if (entity->mp == 0) {
        advance_actor_pending_action(action, context, sprite, entity);
        if (sprite->frameTable != &D_8015CF48) {
            u8 *next_anim_table = &D_8015CF40;

            (sprite->frameTable) = next_anim_table;
            select_sprite_entry(sprite,
                next_anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (sprite->frameTable == &D_8015CF48) {
            action->behavior = 0xD;
            action->phase = 1;
            action->nextBehavior = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(action, context, sprite, &D_8015CF40) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(action, context, sprite, entity);
            return;
        }

        if (action->behavior != 0xE) {
            u8 actor_state = 0xE;

            anim_table = D_8015CF00;
            if (sprite->frameTable != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            action->behavior = actor_state;
        }

        action->flags &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, context, sprite, D_8015CF08) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, entity);
            func_8015C060(action, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(action, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile.bytes.x, sprite->tile.bytes.y);
    sprite->room.raw = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (sprite->tile.packed == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_801598DC(action, context, sprite, entity);
            return;
        }
        if (!(entity->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity,
                        (u8 *)primary_actor_record->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8015A364(action, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = entity->action_flags | 0x4000;
            entity->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                func_801598DC(action, context, sprite, entity);
                return;
            }
        }

        action_state = entity->action_flags & 0x3FFF;
        switch (action_state) {
        case 8:
            if ((func_8015A088(action, context, sprite, entity) << 16) == 0) {
                func_8015A24C(action, context, sprite, entity);
            }
            return;

        case 10:
            func_8015CB14(action, context, sprite, entity);
            return;

        case 9:
            if (D_800DCF5B != 0) {
                break;
            }
            func_8015C234(action, context, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            ActorRecord *player;
            s16 facing_angle;

            facing_angle = get_rounded_facing_and_rounding_flag(
                sprite->tile.bytes.x, sprite->tile.bytes.y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                &direction_flags);
            player = primary_actor_record;
            entity->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(action, context, sprite, &D_8015CF38, update_dungeon_action_behavior_facing_animation_state);
                return;
            }
        }

        case 12:
            update_actor_status_and_food(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(action, context, sprite, &D_8015CF38, update_dungeon_action_behavior_facing_animation_state);
            return;

        case 11:
        case 4:
        default:
            break;
        }
        func_801598DC(action, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_flags);
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
    anim_table = D_8015CF00;
    if (sprite->frameTable == anim_table) {
        return;
    }

    (sprite->frameTable) = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
        0);
}
