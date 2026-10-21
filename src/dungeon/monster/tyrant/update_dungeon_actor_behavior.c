#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"


extern void clear_slots_of_type(void *, s32);
extern void select_sprite_entry(void *, s32, s32);
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
extern void func_80171510(void *, void *, void *, void *);
extern void update_actor_movement_choosing_direction_recording_path(u8 *move_work, void *entry_context, u8 *position, u8 *actor);
extern s32 check_action_eligibility_updates_actor_state_directional_animation_success(void *, void *, void *, void *);
extern void func_80172110(void *, void *, void *, void *);
extern s32 func_80172228(void *, void *, void *, s32);
extern void func_80173900(void *, void *, void *, void *);
extern void handle_kill_actor_clear_flags_fire_burst_tile_post_death_message(void *, void *, void *, void *);

extern s32 D_80170F68;
extern u8 D_80173FB8[];
extern u8 D_80173FC0[];
extern u8 D_80173FF0[];
extern u8 D_80173FF8[];
extern u8 D_80174000[];


typedef struct S_80170F68_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
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
} S_80170F68_1;   /* arg3 in update_dungeon_actor_behavior */

typedef struct S_80170F68_2 {
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
} S_80170F68_2;   /* arg2 in update_dungeon_actor_behavior */


/* Updates a dungeon actor's behavior, facing, and animation from its current state. */
void update_dungeon_actor_behavior(void *actor_arg, void *context_arg, void *map_object_arg, void *actor_state_arg)
{
    u8 *anim_table;
    s32 tile_id;
    s32 distance;
    u32 initial_flags = g_dungeon_status.flags;


    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xE;
        func_80171510(actor_arg, context_arg, map_object_arg, actor_state_arg);
        return;
    }


    if (((S_80170F68_1 *)actor_state_arg)->unk_25 == 0) {
        u8 *inactive_anims;

        advance_actor_pending_action(actor_arg, context_arg, map_object_arg, actor_state_arg);
        if (((S_80170F68_2 *)map_object_arg)->unk_2C != D_80174000) {
            inactive_anims = D_80173FF8;
            (*(void * *)((u8 *)map_object_arg + (0x2C))) = inactive_anims;
            select_sprite_entry(map_object_arg,
                inactive_anims[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170F68_1 *)actor_state_arg)->unk_2A + 0x100)
                    >> 9) & 7],
                0);
        }
        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_AE = 0;
        clear_slots_of_type(actor_state_arg, 0x1A);
        return;
    }

    if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x200) {
        if (((S_80170F68_2 *)map_object_arg)->unk_2C == D_80174000) {
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_8C = 0;
            ((S_80170F68_1 *)actor_state_arg)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, map_object_arg, D_80173FF8)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }

        if (((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 != 0xE) {
            u8 next_state = 0xE;

            anim_table = D_80173FB8;
            if (((S_80170F68_2 *)map_object_arg)->unk_2C != anim_table) {
                (*(void * *)((u8 *)map_object_arg + (0x2C))) = anim_table;
                select_sprite_entry(map_object_arg,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170F68_1 *)actor_state_arg)->unk_2A + 0x100)
                        >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_9A.as_u8 = next_state;
        }

        ((Rec_func_800A9E70_arg0 *)actor_arg)->unk_98 &= 0xFFF3;
        if (((S_80170F68_1 *)actor_state_arg)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, map_object_arg, D_80173FC0)) {
                return;
            }
        }

        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, map_object_arg, actor_state_arg);
            func_80173900(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }

        if ((s16)can_entity_gain_level(actor_state_arg) != 0) {
            process_selected_actor_record(actor_arg, context_arg, map_object_arg, actor_state_arg);
        }
    }

    tile_id = find_active_rect_containing_point(((S_80170F68_2 *)map_object_arg)->unk_24.at00.v,
        ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v);
    ((S_80170F68_2 *)map_object_arg)->unk_26 = tile_id;

    if (((S_80170F68_1 *)actor_state_arg)->unk_6D > 0) {
        if (((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x20) {
            update_actor_status_and_food(actor_state_arg);
            return;
        }
        if (((S_80170F68_2 *)map_object_arg)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            update_actor_movement_choosing_direction_recording_path(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }
        if (!(((S_80170F68_1 *)actor_state_arg)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(actor_state_arg,
                        (u8 *)primary_actor_record->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172228(actor_arg, context_arg, map_object_arg, 0) == 0) {
                return;
            }
            ((S_80170F68_1 *)actor_state_arg)->unk_46 |= 0x4000;
            if (!(((S_80170F68_1 *)actor_state_arg)->unk_46 & 0x8000)) {
                update_actor_movement_choosing_direction_recording_path(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
            }
        }

        switch (((S_80170F68_1 *)actor_state_arg)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)check_action_eligibility_updates_actor_state_directional_animation_success(actor_arg, context_arg, map_object_arg, actor_state_arg) == 0) {
                func_80172110(actor_arg, context_arg, map_object_arg, actor_state_arg);
                return;
            }
            return;
        case 9:
            handle_kill_actor_clear_flags_fire_burst_tile_post_death_message(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *player;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    ((S_80170F68_2 *)map_object_arg)->unk_24.at00.v, ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                ((S_80170F68_1 *)actor_state_arg)->unk_2A = direction;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor_arg, context_arg, map_object_arg, D_80173FF0, &D_80170F68);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_food(actor_state_arg);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_arg, context_arg, map_object_arg, D_80173FF0, &D_80170F68);
            return;
        default:
            update_actor_movement_choosing_direction_recording_path(actor_arg, context_arg, map_object_arg, actor_state_arg);
            return;
        }
    } else if (!(((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x2000)) {
        s32 record_index = (s8)tile_id;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((S_80170F68_1 *)actor_state_arg)->unk_1C & 0x430)) {

                if ((s16)compare_monster_neighbor_values(((S_80170F68_2 *)map_object_arg)->unk_24.at00.v,
                        ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    ((S_80170F68_1 *)actor_state_arg)->unk_2A = get_rounded_facing_and_rounding_flag(
                        ((S_80170F68_2 *)map_object_arg)->unk_24.at00.v,
                            ((S_80170F68_2 *)map_object_arg)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_80170F68_2 *)map_object_arg)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80173FB8;
    if (((S_80170F68_2 *)map_object_arg)->unk_2C == anim_table) {
        return;
    }
    (*(void * *)((u8 *)map_object_arg + (0x2C))) = anim_table;
    select_sprite_entry(map_object_arg,
        ((((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80170F68_1 *)actor_state_arg)->unk_2A + 0x100) >> 9) & 7) + anim_table)[0],
        0);
}
