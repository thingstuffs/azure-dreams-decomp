#include "common.h"
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
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8016BCD8(void *, void *, void *, void *);
extern void func_8016BF1C(void *, void *, void *, void *);
extern s32 func_8016C6D0(void *, void *, void *, void *);
extern void func_8016C894(void *, void *, void *, void *);
extern s32 func_8016C9AC(void *, void *, void *, s32);
extern void func_8016E598(void *, void *, void *, void *);
extern void func_8016E76C(void *, void *, void *, void *);

extern u8 D_8016B760[];
extern u8 D_8016EE88[];
extern u8 D_8016EE98[];
extern u8 D_8016EEE0[];
extern u8 D_8016EEE8[];
extern u8 D_8016EEF0[];

typedef struct ActorSpriteView {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x; u8 y; } bytes;
        u16 packed;
    } tile;
    u8 room;
    u8 pad_27[0x5];
    void * animationTable;
} ActorSpriteView;

void update_actor_behavior_and_idle_delay(void *controller, void *context, void *sprite, ActorRecord *actor)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8016BCD8(controller, context, sprite, actor);
        return;
    }

    if (actor->mp == 0) {
        advance_actor_pending_action(controller, context, sprite, actor);
        if (((ActorSpriteView *)sprite)->animationTable != D_8016EEF0) {
            ((ActorSpriteView *)sprite)->animationTable = D_8016EEE8;
            select_sprite_entry(sprite,
                D_8016EEE8[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)actor->flags1C) & 0x200) {
        if (((ActorSpriteView *)sprite)->animationTable == D_8016EEF0) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            actor->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(controller, context, sprite, D_8016EEE8)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, actor);
            return;
        }

        {
            u8 current_state;
            u8 idle_state;

            current_state = ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8;
            idle_state = 0xE;
            if (current_state != idle_state) {
                anim_table = D_8016EE88;
                if (((ActorSpriteView *)sprite)->animationTable != anim_table) {
                    ((ActorSpriteView *)sprite)->animationTable = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_A0.at00_s16.v = (rand() & 0x1F) + 0xF;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = idle_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (actor->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, D_8016EE98)) {
                return;
            }
        }

        if (((u32)actor->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, actor);
            func_8016E598(controller, context, sprite, actor);
            return;
        }

        if ((can_entity_gain_level(actor) << 16) != 0) {
            process_selected_actor_record(controller, context, sprite, actor);
        }
    }

    room_id = find_active_rect_containing_point(((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y);
    ((ActorSpriteView *)sprite)->room = room_id;

    if (actor->pending_turn_updates > 0) {
        u16 action_state;

        if (((u32)actor->flags1C) & 0x20) {
            update_actor_status_and_food(actor);
            return;
        }
        if (!(((ActorSpriteView *)sprite)->tile.packed == *(u16 *)(&D_80082E80.tile_position.parts.tile_x))) {
            if (!(actor->action_flags & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(actor,
                            (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_8016C9AC(controller, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action_state = actor->action_flags | 0x4000;
                actor->action_flags = action_state;
            }

            if (actor->action_flags & 0x8000) {
                action_state = actor->action_flags & 0x3FFF;
                switch (action_state) {
                case 8:
                    if ((func_8016C6D0(controller, context, sprite, actor) << 16) != 0) {
                        return;
                    }
                    func_8016C894(controller, context, sprite, actor);
                    return;

                case 9:
                    func_8016E76C(controller, context, sprite, actor);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    ActorRecord *player;
                    s16 facing_angle;

                    facing_angle = get_rounded_facing_and_rounding_flag(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &direction_flags);
                    player = D_800814A8;
                    actor->facing = facing_angle;
                    if (player->unk_9A == 0x11) {
                        begin_actor_spell_action(controller, context, sprite, D_8016EEE0, D_8016B760);
                        return;
                    }
                }

                case 12:
                    update_actor_status_and_food(actor);
                    return;

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(controller, context, sprite, D_8016EEE0, D_8016B760);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }
        func_8016BF1C(controller, context, sprite, actor);
        return;
    } else if (!(((u32)actor->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &direction_flags);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((ActorSpriteView *)sprite)->flags & 0x40) {
        return;
    }
    anim_table = D_8016EE88;
    if (((ActorSpriteView *)sprite)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)sprite)->animationTable = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
        0);
}
