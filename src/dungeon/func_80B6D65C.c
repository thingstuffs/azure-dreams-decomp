#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80170E5C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_80170E5C_0;   /* arg0 in update_actor_behavior_facing_and_animation_2 */

typedef struct S_80170E5C_1 {
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
} S_80170E5C_1;   /* arg3 in update_actor_behavior_facing_and_animation_2 */

typedef struct S_80170E5C_2 {
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
} S_80170E5C_2;   /* arg2 in update_actor_behavior_facing_and_animation_2 */


extern void func_80047784(void *, s32, s32);
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
extern void advance_actor_path_script_step(void *, void *, void *, void *);
extern void func_8017162C(void *, void *, void *, void *);
extern s32 func_80171DD8(void *, void *, void *, void *);
extern void select_and_start_target_action(void *, void *, void *, void *);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173AC0(void *, void *, void *, void *);

extern u8 D_80173D0C[];
extern u8 D_80173D14[];
extern u8 D_80173D1C[];
extern u8 D_80173D3C[];
extern u8 D_80173D44[];
extern u8 D_80173D4C[];

/* Update actor behavior, facing, and animation from dungeon state. */
void update_actor_behavior_facing_and_animation_2(void *actor, void *context, void *sprite, void *status)
{
    u8 *anim_table;
    s32 room_id;
    s32 direction_aux;
    s16 anim_ticks;
    u32 initial_flags = g_dungeon_status.flags;


    if (initial_flags & 0x1000) {
        ((S_80170E5C_0 *)actor)->unk_9A = 0xE;
        advance_actor_path_script_step(actor, context, sprite, status);
        return;
    }


    if (((S_80170E5C_1 *)status)->unk_25 == 0) {
        advance_actor_pending_action(actor, context, sprite, status);
        if (((S_80170E5C_2 *)sprite)->unk_2C == D_80173D4C) {
            return;
        }
        (*(void * *)((u8 *)sprite + 0x2C)) = D_80173D44;
        func_80047784(sprite,
            D_80173D44[((g_game_work.view.viewAngle + ((S_80170E5C_1 *)status)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170E5C_1 *)status)->unk_1C & 0x200) {
        if (((S_80170E5C_2 *)sprite)->unk_2C == D_80173D4C) {
            ((S_80170E5C_0 *)actor)->unk_9A = 0xD;
            ((S_80170E5C_0 *)actor)->unk_9B = 1;
            ((S_80170E5C_0 *)actor)->unk_8C = 0;
            ((S_80170E5C_1 *)status)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80173D44)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, status);
            return;
        }

        if (((S_80170E5C_0 *)actor)->unk_9A != 0xE) {
            u8 next_state = 0xE;

            if (((S_80170E5C_2 *)sprite)->unk_2C != D_80173D0C) {
                s32 anim_delay = 10;

                ((S_80170E5C_0 *)actor)->unk_A4.s = anim_delay;
                (*(void * *)((u8 *)sprite + 0x2C)) = D_80173D14;
                func_80047784(sprite,
                    D_80173D14[((g_game_work.view.viewAngle + ((S_80170E5C_1 *)status)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E5C_0 *)actor)->unk_9A = next_state;
        }

        ((S_80170E5C_0 *)actor)->unk_98 &= 0xFFF3;
        if (((S_80170E5C_1 *)status)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80173D1C)) {
                return;
            }
        }

        if (((S_80170E5C_1 *)status)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, status);
            func_80173AC0(actor, context, sprite, status);
            return;
        }

        if ((s16)can_entity_gain_level(status) != 0) {
            process_selected_actor_record(actor, context, sprite, status);
        }
    }

    room_id = find_active_rect_containing_point(((S_80170E5C_2 *)sprite)->unk_24.at00.v, ((S_80170E5C_2 *)sprite)->unk_24.at01.v);
    ((S_80170E5C_2 *)sprite)->unk_26 = room_id;

    if (((S_80170E5C_1 *)status)->unk_6D > 0) {
        if (((S_80170E5C_1 *)status)->unk_1C & 0x20) {
            update_actor_status_and_food(status);
            return;
        }
        if (((S_80170E5C_2 *)sprite)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            func_8017162C(actor, context, sprite, status);
            return;
        }
        if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(status,
                    (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(actor, context, sprite, 0) == 0) {
                return;
            }
            ((S_80170E5C_1 *)status)->unk_46 |= 0x4000;
            if (!(((S_80170E5C_1 *)status)->unk_46 & 0x8000)) {
                func_8017162C(actor, context, sprite, status);
                return;
            }
        }

        switch ((((S_80170E5C_1 *)status)->unk_46 & 0x3FFF) - 1) {
        case 7:
        case 8:
            if ((s16)func_80171DD8(actor, context, sprite, status) == 0) {
                select_and_start_target_action(actor, context, sprite, status);
            }
            return;

        case 4:
        case 5:
        case 6:
            {
                EntityRec *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    ((S_80170E5C_2 *)sprite)->unk_24.at00.v, ((S_80170E5C_2 *)sprite)->unk_24.at01.v,
                    D_80082E80.tileX, D_80082E80.tileY,
                    &direction_aux);
                global_actor = D_800814A8;
                ((S_80170E5C_1 *)status)->unk_2A = direction;
                if (global_actor->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80173D3C, update_actor_behavior_facing_and_animation_2);
                    return;
                }
            }

        case 11:
            update_actor_status_and_food(status);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, D_80173D3C, update_actor_behavior_facing_and_animation_2);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_8017162C(actor, context, sprite, status);
            return;

        }
    }

    if (!(((S_80170E5C_1 *)status)->unk_1C & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((S_80170E5C_1 *)status)->unk_1C & 0x430)) {

                if ((s16)compare_monster_neighbor_values(((S_80170E5C_2 *)sprite)->unk_24.at00.v,
                    ((S_80170E5C_2 *)sprite)->unk_24.at01.v, D_80082E80.tileX,
                    D_80082E80.tileY) != 0) {
                    ((S_80170E5C_1 *)status)->unk_2A = get_rounded_facing_and_rounding_flag(
                        ((S_80170E5C_2 *)sprite)->unk_24.at00.v, ((S_80170E5C_2 *)sprite)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_80170E5C_2 *)sprite)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_80173D0C;
    if (((S_80170E5C_2 *)sprite)->unk_2C == anim_table) {
        return;
    }
    anim_ticks = ((S_80170E5C_0 *)actor)->unk_A4.u - 1;
    ((S_80170E5C_0 *)actor)->unk_A4.s = anim_ticks;
    if (anim_ticks > 0) {
        return;
    }
    ((S_80170E5C_0 *)actor)->unk_A4.s = -1;

    (*(void * *)((u8 *)sprite + 0x2C)) = anim_table;
    func_80047784(sprite,
        anim_table[((g_game_work.view.viewAngle + ((S_80170E5C_1 *)status)->unk_2A + 0x100) >> 9) & 7],
        0);
}
