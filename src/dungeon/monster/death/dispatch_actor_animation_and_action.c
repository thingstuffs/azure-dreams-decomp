#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"


extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void advance_entity_path_state(void *, void *, void *, void *);
extern void func_801721D8(void *, void *, void *, void *);
extern s32 attempt_target_action(void *, void *, void *, void *);
extern void apply_conditional_actor_effect(void *, void *, void *, void *);
extern s32 func_80172B8C(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern s32 D_801719DC;
extern u8 D_80174634[];
extern u8 D_80174644[];
extern u8 D_80174674[];
extern u8 D_8017467C[];
extern u8 D_80174684[];


typedef struct S_801719DC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x2]; s16 v; } at02;
        struct { u8 pad[0x2]; u16 v; } at02u;
    } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    s16 unk_B8;
} S_801719DC_0;   /* arg0 in dispatch_actor_animation_and_action */

typedef struct S_801719DC_1 {
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
} S_801719DC_1;   /* arg3 in dispatch_actor_animation_and_action */

typedef struct S_801719DC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
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
} S_801719DC_2;   /* arg2 in dispatch_actor_animation_and_action */


/* Update actor animation, facing, and action dispatch from dungeon state. */
void dispatch_actor_animation_and_action(void *motion_in, void *context_in, void *entity_in, void *actor_in)
{
    s32 direction_aux;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_801719DC_0 *)motion_in)->unk_9A = 0xE;
        advance_entity_path_state(motion_in, context_in, entity_in, actor_in);
        return;
    }
    if (((S_801719DC_1 *)actor_in)->unk_25 == 0) {
        void *anim_table;

        advance_actor_pending_action(motion_in, context_in, entity_in, actor_in);
        if (((S_801719DC_2 *)entity_in)->unk_2C == D_80174684) {
            return;
        }
        anim_table = D_8017467C;
        (*(void * *)((u8 *)entity_in + (0x2C))) = anim_table;
        select_sprite_entry(entity_in,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801719DC_1 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_801719DC_1 *)actor_in)->unk_1C & 0x200) {
        if (((S_801719DC_2 *)entity_in)->unk_2C == D_80174684) {
            ((S_801719DC_0 *)motion_in)->unk_9A = 0xD;
            ((S_801719DC_0 *)motion_in)->unk_9B = 1;
            ((S_801719DC_0 *)motion_in)->unk_8C = 0;
            ((S_801719DC_1 *)actor_in)->unk_1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(motion_in, context_in, entity_in, D_8017467C) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_801719DC_1 *)actor_in)->unk_1C & 0x100) {
            begin_pushed_actor_move(motion_in, context_in, entity_in, actor_in);
            return;
        }

        {
            s32 current_state;
            u32 next_state;
            void *current_anim;
            void *anim_table;
            s32 motion_value;

            current_state = ((S_801719DC_0 *)motion_in)->unk_9A;

            next_state = 0xE;
            if (current_state != next_state) {
                current_anim = ((S_801719DC_2 *)entity_in)->unk_2C;
                anim_table = D_80174634;
                if (current_anim != anim_table) {
                    (*(void * *)((u8 *)entity_in + (0x2C))) = anim_table;
                    select_sprite_entry(entity_in,
                        ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801719DC_1 *)actor_in)->unk_2A + 0x100)
                            >> 9) & 7],
                        1);
                    ((S_801719DC_2 *)entity_in)->unk_05 = 1;
                    motion_value = ((S_801719DC_0 *)motion_in)->unk_A4.at00.v;
                    ((S_801719DC_0 *)motion_in)->unk_A4.at02.v = 0;
                    ((S_801719DC_0 *)motion_in)->unk_B8 = 0;
                    ((S_801719DC_0 *)motion_in)->unk_AC = 0;
                    ((S_801719DC_0 *)motion_in)->unk_B0 = 0;
                    ((S_801719DC_0 *)motion_in)->unk_A8 = motion_value;
                }
                ((S_801719DC_0 *)motion_in)->unk_9A = next_state;
            }
        }

        ((S_801719DC_0 *)motion_in)->unk_98 &= 0xFFF3;
        ((S_801719DC_1 *)actor_in)->unk_1C |= 0x40000;

        if (((S_801719DC_1 *)actor_in)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(motion_in, context_in, entity_in, D_80174644) != 0) {
                return;
            }
        }

        if (((S_801719DC_1 *)actor_in)->unk_1C & 0x80000) {
            u16 base_offset;
            u16 offset_delta;
            s32 motion_value;

            begin_actor_move_to_target_facing(motion_in, context_in, entity_in, actor_in);
            base_offset = ((S_801719DC_0 *)motion_in)->unk_92;
            offset_delta = ((S_801719DC_0 *)motion_in)->unk_A4.at02u.v;
            motion_value = ((S_801719DC_0 *)motion_in)->unk_A4.at00.v;
            ((S_801719DC_0 *)motion_in)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)motion_in)->unk_B8 = 0;
            ((S_801719DC_0 *)motion_in)->unk_AC = 0;
            ((S_801719DC_0 *)motion_in)->unk_B0 = 0;
            ((S_801719DC_0 *)motion_in)->unk_92 = base_offset - offset_delta;
            ((S_801719DC_0 *)motion_in)->unk_A8 = motion_value;
            func_801743F0(motion_in, context_in, entity_in, actor_in);
            return;
        }

        if ((can_entity_gain_level(actor_in) << 16) != 0) {
            process_selected_actor_record(motion_in, context_in, entity_in, actor_in);
        }
    }

    room_id = find_active_rect_containing_point(((S_801719DC_2 *)entity_in)->unk_24.at00.v, ((S_801719DC_2 *)entity_in)->unk_24.at01.v);
    ((S_801719DC_2 *)entity_in)->unk_26 = room_id;

    if (((S_801719DC_1 *)actor_in)->unk_6D > 0) {
        if (((S_801719DC_1 *)actor_in)->unk_1C & 0x20) {
            update_actor_status_and_mp(actor_in);
            return;
        }
        if (((S_801719DC_2 *)entity_in)->unk_24.at00u.v == *(u16 *)(&reference_tile_object.tile_position.parts.tile_x)) {
            func_801721D8(motion_in, context_in, entity_in, actor_in);
            return;
        }
        if (!(((S_801719DC_1 *)actor_in)->unk_46 & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(actor_in,
                        (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172B8C(motion_in, context_in, entity_in, 0) << 16) == 0) {
                return;
            }
            action_state = ((S_801719DC_1 *)actor_in)->unk_46 | 0x4000;
            ((S_801719DC_1 *)actor_in)->unk_46 = action_state;
            if (!(action_state & 0x8000)) {
                func_801721D8(motion_in, context_in, entity_in, actor_in);
                return;
            }
        }

        action_state = ((S_801719DC_1 *)actor_in)->unk_46 & 0x3FFF;
        switch (action_state - 1) {

        case 7:
        case 8:
            if ((attempt_target_action(motion_in, context_in, entity_in, actor_in) << 16) != 0) {
                return;
            }
            apply_conditional_actor_effect(motion_in, context_in, entity_in, actor_in);
            return;

        case 4:
        case 5:
        case 6:
        {
            ActorRecord *player;
            s16 heading;

            heading = get_rounded_facing_and_rounding_flag(
                ((S_801719DC_2 *)entity_in)->unk_24.at00.v, ((S_801719DC_2 *)entity_in)->unk_24.at01.v,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                &direction_aux);
            player = primary_actor_record;
            ((S_801719DC_1 *)actor_in)->unk_2A = heading;
            if (player->unk_9A == 0x11) {
                begin_actor_spell_action(motion_in, context_in, entity_in, D_80174674, &D_801719DC);
                return;
            }
        }

        case 11:
            update_actor_status_and_mp(actor_in);
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(motion_in, context_in, entity_in, D_80174674, &D_801719DC);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_801721D8(motion_in, context_in, entity_in, actor_in);
            return;
        }
    }

    if (!(((S_801719DC_1 *)actor_in)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((S_801719DC_1 *)actor_in)->unk_1C & 0x430)) {

                if ((test_neighbor_position_relation(
                        ((S_801719DC_2 *)entity_in)->unk_24.at00.v, ((S_801719DC_2 *)entity_in)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    ((S_801719DC_1 *)actor_in)->unk_2A = get_rounded_facing_and_rounding_flag(
                        ((S_801719DC_2 *)entity_in)->unk_24.at00.v, ((S_801719DC_2 *)entity_in)->unk_24.at01.v,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (((S_801719DC_2 *)entity_in)->unk_14 & 0x40) {
        return;
    }
    {
        void *anim_table = D_80174634;
        s32 motion_value;

        if (((S_801719DC_2 *)entity_in)->unk_2C != anim_table) {
            (*(void * *)((u8 *)entity_in + (0x2C))) = anim_table;
            select_sprite_entry(entity_in,
                ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801719DC_1 *)actor_in)->unk_2A + 0x100) >> 9) & 7],
                1);
            ((S_801719DC_2 *)entity_in)->unk_05 = 1;
            motion_value = ((S_801719DC_0 *)motion_in)->unk_A4.at00.v;
            ((S_801719DC_0 *)motion_in)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)motion_in)->unk_B8 = 0;
            ((S_801719DC_0 *)motion_in)->unk_AC = 0;
            ((S_801719DC_0 *)motion_in)->unk_B0 = 0;
            ((S_801719DC_0 *)motion_in)->unk_A8 = motion_value;
        }
    }
}
