#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171E20_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80171E20_0;   /* arg0 in update_actor_dungeon_behavior_and_animation */

typedef struct S_80171E20_1 {
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
} S_80171E20_1;   /* arg3 in update_actor_dungeon_behavior_and_animation */

typedef struct S_80171E20_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80171E20_2;   /* arg2 in update_actor_dungeon_behavior_and_animation */


extern void func_80047784(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 compare_monster_neighbor_values(u8, u8, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_80172384(void *, void *, void *, void *);
extern void initialize_item_sprite_frame(void *, void *, void *, void *);
extern s32 advance_item_action_sequence(void *, void *, void *, void *);
extern void func_80172F38(void *, void *, void *, void *);
extern s32 func_80173050(void *, void *, void *, s32);
extern void func_80174890(void *, void *, void *, void *);
extern void begin_actor_directional_target_action(void *, void *, void *, void *);

extern u8 D_801753BC[];
extern u8 D_801753C4[];
extern u8 D_801753F4[];
extern u8 D_801753FC[];
extern u8 D_80175404[];

/* Updates an actor's dungeon behavior, facing, and animation. */
void update_actor_dungeon_behavior_and_animation(void *actor_in, void *actor_data_in, void *sprite_in, void *status_in)
{
    u32 initial_flags = g_dungeon_status.flags;
    s16 distance;
    s32 status_flags;
    s8 tile_id;
    s16 facing;
    u16 action_flags;
    u8 *anim_table;
    EntityRec *player;

    if (initial_flags & 0x1000) {
        ((S_80171E20_0 *)actor_in)->unk_9A = 14;
        func_80172384(actor_in, actor_data_in, sprite_in, status_in);
        return;
    }


    if (((S_80171E20_1 *)status_in)->unk_25 == 0) {
        advance_actor_pending_action(actor_in, actor_data_in, sprite_in, status_in);
        if (((S_80171E20_2 *)sprite_in)->unk_2C == D_80175404) {
            return;
        }
        {
            u8 *early_anim_table = D_801753FC;
            (*(u8 * *)((u8 *)sprite_in + 0x2C)) = early_anim_table;
            func_80047784(
                sprite_in,
                early_anim_table[((g_game_work.view.viewAngle + ((S_80171E20_1 *)status_in)->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171E20_1 *)status_in)->unk_1C & 0x200) {
        if (((S_80171E20_2 *)sprite_in)->unk_2C == D_80175404) {
            ((S_80171E20_0 *)actor_in)->unk_9A = 13;
            ((S_80171E20_0 *)actor_in)->unk_9B = 1;
            ((S_80171E20_0 *)actor_in)->unk_8C = 0;
            ((S_80171E20_1 *)status_in)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_in, actor_data_in, sprite_in, D_801753FC) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((S_80171E20_1 *)status_in)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }

        {
            u8 current_state = ((S_80171E20_0 *)actor_in)->unk_9A;
            u32 next_state = 14;

            if (current_state != next_state) {
                anim_table = D_801753BC;
                if (((S_80171E20_2 *)sprite_in)->unk_2C != anim_table) {
                    (*(u8 * *)((u8 *)sprite_in + 0x2C)) = anim_table;
                    func_80047784(
                        sprite_in,
                        anim_table[((g_game_work.view.viewAngle + ((S_80171E20_1 *)status_in)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80171E20_0 *)actor_in)->unk_9A = next_state;
            }
        }

        ((S_80171E20_0 *)actor_in)->unk_98 &= 0xFFF3;

        if (((S_80171E20_1 *)status_in)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, actor_data_in, sprite_in, D_801753C4) != 0) {
                return;
            }
        }

        if (((S_80171E20_1 *)status_in)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, actor_data_in, sprite_in, status_in);
            func_80174890(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }

        if ((s16)can_entity_gain_level(status_in) != 0) {
            process_selected_actor_record(actor_in, actor_data_in, sprite_in, status_in);
        }
    }

    tile_id = find_active_rect_containing_point(((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v);
    ((S_80171E20_2 *)sprite_in)->unk_26 = tile_id;

    if (((S_80171E20_1 *)status_in)->unk_6D > 0) {
        if (((S_80171E20_1 *)status_in)->unk_1C & 0x20) {
            update_actor_status_and_food(status_in);
            return;
        }
        if (((S_80171E20_2 *)sprite_in)->unk_24.at00u.v == *(u16 *)(&D_80082E80.tileX)) {
            initialize_item_sprite_frame(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }
        action_flags = ((S_80171E20_1 *)status_in)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        status_in, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80173050(actor_in, actor_data_in, sprite_in, 0) == 0) {
                return;
            }
            action_flags = ((S_80171E20_1 *)status_in)->unk_46 | 0x4000;
            ((S_80171E20_1 *)status_in)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                initialize_item_sprite_frame(actor_in, actor_data_in, sprite_in, status_in);
            return;
            }
        }

        switch (((S_80171E20_1 *)status_in)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)advance_item_action_sequence(actor_in, actor_data_in, sprite_in, status_in) != 0) {
                return;
            }
            func_80172F38(actor_in, actor_data_in, sprite_in, status_in);
            return;
        case 9:
            begin_actor_directional_target_action(actor_in, actor_data_in, sprite_in, status_in);
            return;
        case 5:
        case 6:
        case 7:
            facing = get_rounded_facing_and_rounding_flag(
                ((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v,
                D_80082E80.tileX, D_80082E80.tileY, &distance);
            player = D_800814A8;
            ((S_80171E20_1 *)status_in)->unk_2A = facing;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(actor_in, actor_data_in, sprite_in, D_801753F4, update_actor_dungeon_behavior_and_animation);
                return;
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_food(status_in);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_in, actor_data_in, sprite_in, D_801753F4, update_actor_dungeon_behavior_and_animation);
            return;
        default:
            initialize_item_sprite_frame(actor_in, actor_data_in, sprite_in, status_in);
            return;
        }
    }

    status_flags = ((S_80171E20_1 *)status_in)->unk_1C;
    if (!(status_flags & 0x2000)) {
        if ((tile_id < 0) ||
            !(D_800E2970[tile_id].flags & 2)) {
            if (!(status_flags & 0x430)) {
                if ((s16)compare_monster_neighbor_values(
                        ((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY) != 0) {
                    ((S_80171E20_1 *)status_in)->unk_2A = get_rounded_facing_and_rounding_flag(
                        ((S_80171E20_2 *)sprite_in)->unk_24.at00.v, ((S_80171E20_2 *)sprite_in)->unk_24.at01.v,
                        D_80082E80.tileX, D_80082E80.tileY, &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_80171E20_2 *)sprite_in)->unk_14 & 0x40) {
        return;
    }
    anim_table = D_801753BC;
    if (((S_80171E20_2 *)sprite_in)->unk_2C == anim_table) {
        return;
    }

    (*(u8 * *)((u8 *)sprite_in + 0x2C)) = anim_table;
    func_80047784(
        sprite_in,
        anim_table[((g_game_work.view.viewAngle + ((S_80171E20_1 *)status_in)->unk_2A + 0x100) >> 9) & 7],
        0);
}
