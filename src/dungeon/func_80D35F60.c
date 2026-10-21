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
extern s32 rand(void);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, ActorSpriteView *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8014DCD8(void *, void *, void *, void *);
extern void func_8014DF1C(void *, void *, void *, void *);
extern s32 func_8014E6D0(void *, void *, void *, void *);
extern void func_8014E894(void *, void *, void *, void *);
extern s32 func_8014E9AC(void *, void *, void *, s32);
extern void func_80150598(void *, void *, void *, void *);
extern void func_8015076C(void *, void *, void *, void *);

extern u8 D_80150E88[];
extern u8 D_80150E98[];
extern u8 D_80150EE0[];
extern u8 D_80150EE8[];
extern u8 D_80150EF0[];

/* Update the actor's dungeon behavior, facing, and directional animation. */
void update_actor_behavior_variant_h(ActorActionView *action, void *context, ActorSpriteView *sprite, ActorRecord *actor)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        action->behavior = 0xE;
        func_8014DCD8(action, context, sprite, actor);
        return;
    }

    if (actor->mp == 0) {
        advance_actor_pending_action(action, context, sprite, actor);
        if (sprite->frameTable != D_80150EF0) {
            (sprite->frameTable) = D_80150EE8;
            select_sprite_entry(sprite,
                D_80150EE8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor->flags1C) & 0x200) {
        if (sprite->frameTable == D_80150EF0) {
            action->behavior = 0xD;
            action->phase = 1;
            action->nextBehavior = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action, context, sprite, D_80150EE8)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & 0x100) {
            begin_pushed_actor_move(action, context, sprite, actor);
            return;
        }

        {
            u8 current_state;
            u8 idle_state;

            current_state = action->behavior;
            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = D_80150E88;
                if (sprite->frameTable != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
                action->idleElapsed = 0;
                action->idleDelay = (rand() & 0x1F) + 0xF;
                action->behavior = idle_state;
            }
        }

        action->flags &= 0xFFF3;
        if (actor->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, context, sprite, D_80150E98)) {
                return;
            }
        }

        if (((u32)actor->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(action, context, sprite, actor);
            func_80150598(action, context, sprite, actor);
            return;
        }

        if ((can_entity_gain_level(actor) << 16) != 0) {
            process_selected_actor_record(action, context, sprite, actor);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile.bytes.x, sprite->tile.bytes.y);
    sprite->room.raw = room_id;

    if (actor->pending_turn_updates > 0) {
        u16 action_state;

        if (((u32)actor->flags1C) & 0x20) {
            update_actor_status_and_food(actor);
            return;
        }
        if (!(sprite->tile.packed == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x))) {
            if (!(actor->action_flags & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(actor,
                            (u8 *)primary_actor_record->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_8014E9AC(action, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = actor->action_flags | 0x4000;
                actor->action_flags = action_state;
            }

            if (actor->action_flags & 0x8000) {
                action_state = actor->action_flags & 0x3FFF;
                switch (action_state) {
                case 8:
                    if ((func_8014E6D0(action, context, sprite, actor) << 16) != 0) {
                        return;
                    }
                    func_8014E894(action, context, sprite, actor);
                    return;

                case 9:
                    func_8015076C(action, context, sprite, actor);
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
                    actor->facing = facing_angle;
                    if (player->unk_9A == 0x11) {
                        begin_actor_spell_action(action, context, sprite, D_80150EE0, update_actor_behavior_variant_h);
                        return;
                    }
                }

                case 12:
                    update_actor_status_and_food(actor);
                    return;

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(action, context, sprite, D_80150EE0, update_actor_behavior_variant_h);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }
        func_8014DF1C(action, context, sprite, actor);
        return;
    } else if (!(((u32)actor->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        sprite->tile.bytes.x, sprite->tile.bytes.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
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
    anim_table = D_80150E88;
    if (sprite->frameTable == anim_table) {
        return;
    }
    (sprite->frameTable) = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
}
