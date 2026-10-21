#include "common.h"
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
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8015FCD4(void *, void *, void *, void *);
extern void func_8015FF40(void *, void *, void *, void *);
extern s32 func_80160710(void *, void *, void *, void *);
extern void func_801608D4(void *, void *, void *, void *);
extern s32 func_801609EC(void *, void *, void *, s32);
extern void func_801623E8(void *, void *, void *, void *);
extern void func_80162928(void *, void *, void *, void *);

extern s32 D_8015F728;
extern u8 D_80162DEC[];
extern u8 D_80162DFC[];
extern u8 D_80162E2C[];
extern u8 D_80162E44[];
extern u8 D_80162E4C[];

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

void func_8015F728(void *controller, void *context, void *sprite, ActorRecord *creature)
{
    u8 *anim_table;
    s32 direction_flags;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xE;
        func_8015FCD4(controller, context, sprite, creature);
        return;
    }

    if (creature->mp == 0) {
        advance_actor_pending_action(controller, context, sprite, creature);
        if (((ActorSpriteView *)sprite)->animationTable == D_80162E4C) {
            return;
        }
        ((ActorSpriteView *)sprite)->animationTable = D_80162E44;
        select_sprite_entry(sprite,
            D_80162E44[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((ActorSpriteView *)sprite)->animationTable == D_80162E4C) {
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)controller)->unk_8C = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(controller, context, sprite, D_80162E44) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            begin_pushed_actor_move(controller, context, sprite, creature);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = D_80162DEC;
                if (((ActorSpriteView *)sprite)->animationTable != anim_table) {
                    ((ActorSpriteView *)sprite)->animationTable = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)controller)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)controller)->unk_98 &= 0xFFF3;
        if (creature->unk_64 != 0) {
            if (begin_ready_actor_directional_action(controller, context, sprite, D_80162DFC) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(controller, context, sprite, creature);
            func_801623E8(controller, context, sprite, creature);
            ((ActorSpriteView *)sprite)->animationTable = D_80162DEC;
            select_sprite_entry(sprite,
                D_80162DEC[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)controller)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            process_selected_actor_record(controller, context, sprite, creature);
        }
    }

    room_id = find_active_rect_containing_point(((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y);
    ((ActorSpriteView *)sprite)->room = room_id;

    if (creature->pending_turn_updates > 0) {
        if (((u32)creature->flags1C) & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if (((ActorSpriteView *)sprite)->tile.packed == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_8015FF40(controller, context, sprite, creature);
            return;
        }
        if (!(creature->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature,
                    (u8 *)primary_actor_record->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801609EC(controller, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature->action_flags | 0x4000;
            creature->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                func_8015FF40(controller, context, sprite, creature);
                return;
            }
        }

        action_flags = creature->action_flags & 0x3FFF;
        switch (action_flags) {
        case 8:
            if ((func_80160710(controller, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_801608D4(controller, context, sprite, creature);
            return;

        case 9:
            func_80162928(controller, context, sprite, creature);
            return;

        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_flags);
                player = primary_actor_record;
                creature->facing = heading;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(controller, context, sprite, D_80162E2C, &D_8015F728);
                    return;
                }
            }

        case 12:
            update_actor_status_and_food(creature);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(controller, context, sprite, D_80162E2C, &D_8015F728);
            return;

        case 10:
        default:
            func_8015FF40(controller, context, sprite, creature);
            return;
        }
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                    ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = get_rounded_facing_and_rounding_flag(
                        ((ActorSpriteView *)sprite)->tile.bytes.x, ((ActorSpriteView *)sprite)->tile.bytes.y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
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
    anim_table = D_80162DEC;
    if (((ActorSpriteView *)sprite)->animationTable == anim_table) {
        return;
    }
    ((ActorSpriteView *)sprite)->animationTable = anim_table;
    select_sprite_entry(sprite,
        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
        0);
}
