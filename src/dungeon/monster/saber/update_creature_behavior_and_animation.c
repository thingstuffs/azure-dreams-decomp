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
extern void advance_entity_along_stored_path(void *, void *, void *, void *);
extern void func_80171F40(void *, void *, void *, void *);
extern s32 func_80172710(void *, void *, void *, void *);
extern void func_801728D4(void *, void *, void *, void *);
extern s32 func_801729EC(void *, void *, void *, s32);
extern void update_timed_effect_size_and_position(void *, void *, void *, void *);
extern void clear_actor_flag_and_apply_effect(void *, void *, void *, void *);

extern s32 D_80171728;
extern u8 D_80174DEC[];
extern u8 D_80174DFC[];
extern u8 D_80174E2C[];
extern u8 D_80174E44[];
extern u8 D_80174E4C[];


typedef struct S_80171728_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171728_2;   /* arg2 in update_creature_behavior_and_animation_2 */


/* Updates creature behavior, facing, and animation from dungeon and action state. */
void update_creature_behavior_and_animation_2(void *actor_in, void *context_in, void *sprite, EntityRec *creature_in)
{
    u8 *anim_table;
    s32 distance;
    s8 room_id;
    u16 action_flags;
    u32 initial_flags = g_dungeon_status.flags;

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = 0xE;
        advance_entity_along_stored_path(actor_in, context_in, sprite, creature_in);
        return;
    }

    if (creature_in->tileY == 0) {
        advance_actor_pending_action(actor_in, context_in, sprite, creature_in);
        if (((S_80171728_2 *)sprite)->unk_2C == D_80174E4C) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80174E44;
        select_sprite_entry(sprite,
            D_80174E44[((g_game_work.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature_in->flags1C) & 0x200) {
        if (((S_80171728_2 *)sprite)->unk_2C == D_80174E4C) {
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_8C = 0;
            creature_in->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor_in, context_in, sprite, D_80174E44) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature_in->flags1C) & 0x100) {
            begin_pushed_actor_move(actor_in, context_in, sprite, creature_in);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8;
            u32 next_state;

            next_state = 0xE;
            if (current_state != next_state) {
                anim_table = D_80174DEC;
                if (((S_80171728_2 *)sprite)->unk_2C != anim_table) {
                    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)actor_in)->unk_9A.as_u8 = next_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)actor_in)->unk_98 &= 0xFFF3;
        if (creature_in->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, context_in, sprite, D_80174DFC) != 0) {
                return;
            }
        }

        if (((u32)creature_in->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, context_in, sprite, creature_in);
            update_timed_effect_size_and_position(actor_in, context_in, sprite, creature_in);
            (*(void * *)((u8 *)sprite + 0x2C)) = D_80174DEC;
            select_sprite_entry(sprite,
                D_80174DEC[((g_game_work.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)actor_in)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((can_entity_gain_level(creature_in) << 16) != 0) {
            process_selected_actor_record(actor_in, context_in, sprite, creature_in);
        }
    }

    room_id = find_active_rect_containing_point(((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v);
    ((S_80171728_2 *)sprite)->unk_26 = room_id;

    if (creature_in->unk_6D > 0) {
        if (((u32)creature_in->flags1C) & 0x20) {
            update_actor_status_and_food(creature_in);
            return;
        }
        if (((S_80171728_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_80171F40(actor_in, context_in, sprite, creature_in);
            return;
        }
        if (!(creature_in->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature_in,
                    (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801729EC(actor_in, context_in, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature_in->unk_46 | 0x4000;
            creature_in->unk_46 = action_flags;
            if (!(action_flags & 0x8000)) {
                func_80171F40(actor_in, context_in, sprite, creature_in);
                return;
            }
        }

        action_flags = creature_in->unk_46 & 0x3FFF;
        switch (action_flags) {
        case 8:
            if ((func_80172710(actor_in, context_in, sprite, creature_in) << 16) != 0) {
                return;
            }
            func_801728D4(actor_in, context_in, sprite, creature_in);
            return;

        case 9:
            clear_actor_flag_and_apply_effect(actor_in, context_in, sprite, creature_in);
            return;

        case 5:
        case 6:
        case 7:
            {
                EntityRec *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &distance);
                player = D_800814A8;
                creature_in->facing = heading;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor_in, context_in, sprite, D_80174E2C, &D_80171728);
                    return;
                }
            }

        case 12:
            update_actor_status_and_food(creature_in);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_in, context_in, sprite, D_80174E2C, &D_80171728);
            return;

        case 10:
        default:
            func_80171F40(actor_in, context_in, sprite, creature_in);
            return;
        }
    }

    if (!(((u32)creature_in->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature_in->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                    ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    creature_in->facing = get_rounded_facing_and_rounding_flag(
                        ((S_80171728_2 *)sprite)->unk_24.at00.v, ((S_80171728_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_80171728_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174DEC;
    if (((S_80171728_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    select_sprite_entry(sprite,
        *(u8 *)(((((g_game_work.view.viewAngle + creature_in->facing + 0x100) >> 9) & 7)) + (u32)anim_table),
        0);
}
