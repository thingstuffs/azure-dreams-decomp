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
extern void func_80171684(void *, void *, void *, void *);
extern void func_801718DC(void *, void *, void *, void *);
extern s32 func_80172088(void *, void *, void *, void *);
extern void func_8017224C(void *, void *, void *, void *);
extern s32 advance_actor_states(void *, void *, void *, s32);
extern void func_80174060(void *, void *, void *, void *);
extern void start_the_actor_s_attack_step_clear_hex_71_busy_bit_latch(void *, void *, void *, void *);
extern void clear_the_state_flag_allowed_resets_entity_selects_directional(void *, void *, void *, void *);

extern u8 D_800DCF5B;
extern u8 D_80174F00[];
extern u8 D_80174F08[];
extern u8 D_80174F38;
extern u8 D_80174F40;
extern u8 D_80174F48;


typedef struct S_801710F4_2 {
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
} S_801710F4_2;   /* arg2 in update_dungeon_actor_behavior_facing_animation_state */


/* Updates dungeon actor behavior, facing, and animation from its current state. */
void update_dungeon_actor_behavior_facing_animation_state(void *actor, void *context, void *sprite, EntityRec *entity)
{
    u8 *anim_table;
    s32 distance;
    s8 room_id;
    u16 action_state;
    u16 initial_flags = g_dungeon_status.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xE;
        func_80171684(actor, context, sprite, entity);
        return;
    }


    if (entity->tileY == 0) {
        advance_actor_pending_action(actor, context, sprite, entity);
        if (((S_801710F4_2 *)sprite)->unk_2C != &D_80174F48) {
            u8 *next_anim_table = &D_80174F40;

            (*(void * *)((u8 *)sprite + 0x2C)) = next_anim_table;
            select_sprite_entry(sprite,
                *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) +
                        (u32)next_anim_table),
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & 0x200) {
        if (((S_801710F4_2 *)sprite)->unk_2C == &D_80174F48) {
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, &D_80174F40) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 != 0xE) {
            u8 actor_state = 0xE;

            anim_table = D_80174F00;
            if (((S_801710F4_2 *)sprite)->unk_2C != anim_table) {
                (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor)->unk_9A.as_u8 = actor_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor)->unk_98 &= 0xFFF3;
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174F08) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_80174060(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v);
    ((S_801710F4_2 *)sprite)->unk_26 = room_id;

    if (entity->unk_6D > 0) {
        if (((u32)entity->flags1C) & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (((S_801710F4_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
            func_801718DC(actor, context, sprite, entity);
            return;
        }
        if (!(entity->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(entity,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((advance_actor_states(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = entity->unk_46 | 0x4000;
            entity->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                func_801718DC(actor, context, sprite, entity);
                return;
            }
        }

        action_state = entity->unk_46 & 0x3FFF;
        switch (action_state) {
        case 8:
            if ((func_80172088(actor, context, sprite, entity) << 16) == 0) {
                func_8017224C(actor, context, sprite, entity);
            }
            return;

        case 10:
            clear_the_state_flag_allowed_resets_entity_selects_directional(actor, context, sprite, entity);
            return;

        case 9:
            if (D_800DCF5B != 0) {
                break;
            }
            start_the_actor_s_attack_step_clear_hex_71_busy_bit_latch(actor, context, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            EntityRec *player;
            s16 facing_angle;

            facing_angle = get_rounded_facing_and_rounding_flag(
                ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                &distance);
            player = D_800814A8;
            entity->facing = facing_angle;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(actor, context, sprite, &D_80174F38, update_dungeon_actor_behavior_facing_animation_state);
                return;
            }
        }

        case 12:
            update_actor_status_and_food(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor, context, sprite, &D_80174F38, update_dungeon_actor_behavior_facing_animation_state);
            return;

        case 11:
        case 4:
        default:
            break;
        }
        func_801718DC(actor, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                        ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        ((S_801710F4_2 *)sprite)->unk_24.at00.v, ((S_801710F4_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_801710F4_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80174F00;
    if (((S_801710F4_2 *)sprite)->unk_2C == anim_table) {
        return;
    }

    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    select_sprite_entry(sprite,
        *(u8 *)((u32)(((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) +
                (u32)anim_table),
        0);
}
