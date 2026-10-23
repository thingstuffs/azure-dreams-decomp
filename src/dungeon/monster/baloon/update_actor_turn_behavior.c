#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/level/scripted_boundary.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

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
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void advance_baloon_along_path(void *, s32, SpriteFrameState *, void *);
extern void func_801726EC(void *, void *, void *, void *);
extern s32 initialize_directional_object(void *, void *, void *, void *);
extern void update_actor_status_and_motion(void *, void *, void *, void *);
extern s32 func_801731DC(void *, void *, void *, s32);
extern void func_8017531C(void *, void *, void *, void *);
extern void clear_high_flag_and_update_counter(void *, void *, void *, void *);
extern void update_actor_counter_and_status(void *, void *, void *, void *);


extern u8 baloon_default_frames[];
extern u8 D_800E2358[];
extern u8 baloon_attack_frames;
extern u8 D_800E23A0[];
extern u8 D_800E23A8[];
extern s32 baloon_action_resume_address;

typedef struct S_80171F1C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
} S_80171F1C_0;   /* arg0 in update_actor_turn_behavior */

/* Update actor movement, animation, and action handling for the dungeon turn. */
void update_actor_turn_behavior(void *motion_arg, void *actor_index_arg, SpriteFrameState *actor_arg, void *move_data_arg)
{
    EntityRec *move_data;
    s32 direction_flags;
    s8 room_id;
    u16 action_state;
    u32 initial_flags = g_dungeon_status.flags;

    move_data = move_data_arg;

    if (initial_flags & 0x1000) {
        ((S_80171F1C_0 *)motion_arg)->unk_9A = 0xE;
        advance_baloon_along_path(motion_arg, (s32)actor_index_arg, actor_arg, move_data);
        return;
    }

    if (move_data->tileY == 0) {
        void *anim_table;

        advance_actor_pending_action(motion_arg, actor_index_arg, actor_arg, move_data);
        if (actor_arg->frameTable == D_800E23A8) {
            return;
        }
        anim_table = D_800E23A0;
        (actor_arg->frameTable) = anim_table;
        select_sprite_entry(actor_arg,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + move_data->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)move_data->flags1C) & ACTOR_ASLEEP) {
        if (actor_arg->frameTable == D_800E23A8) {
            ((S_80171F1C_0 *)motion_arg)->unk_9A = 0xD;
            ((S_80171F1C_0 *)motion_arg)->unk_9B = 1;
            ((S_80171F1C_0 *)motion_arg)->unk_8C = 0;
            move_data->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(motion_arg, actor_index_arg, actor_arg, D_800E23A0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)move_data->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(motion_arg, actor_index_arg, actor_arg, move_data);
            return;
        }

        {
            u8 current_state = ((S_80171F1C_0 *)motion_arg)->unk_9A;
            u32 idle_state = 0xE;
            void *current_anim;
            void *anim_table;

            if (current_state != idle_state) {
                ((S_80171F1C_0 *)motion_arg)->unk_9A = idle_state;
            }
            current_anim = actor_arg->frameTable;
            anim_table = baloon_default_frames;
            if (current_anim != anim_table) {
                (actor_arg->frameTable) = anim_table;
                select_sprite_entry(actor_arg,
                    ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + move_data->facing + 0x100) >> 9) & 7],
                    0);
                actor_arg->unk_05 = 1;
                ((S_80171F1C_0 *)motion_arg)->unk_A2.s = 0;
                ((S_80171F1C_0 *)motion_arg)->unk_9E = 0;
            }
        }

        move_data->flags1C |= 0x40000;
        ((S_80171F1C_0 *)motion_arg)->unk_98 &= 0xFFF7;

        if (move_data->unk_64 != 0) {
            if (begin_ready_actor_directional_action(motion_arg, actor_index_arg, actor_arg, D_800E2358) != 0) {
                return;
            }
        }

        if (((u32)move_data->flags1C) & ACTOR_LIFTED) {
            s16 base_height;

            begin_actor_move_to_target_facing(motion_arg, actor_index_arg, actor_arg, move_data);
            base_height = ((S_80171F1C_0 *)motion_arg)->unk_92.u - ((S_80171F1C_0 *)motion_arg)->unk_A2.u;
            ((S_80171F1C_0 *)motion_arg)->unk_A2.s = 0;
            ((S_80171F1C_0 *)motion_arg)->unk_9E = 0;
            ((S_80171F1C_0 *)motion_arg)->unk_92.s = base_height;
            func_8017531C(motion_arg, actor_index_arg, actor_arg, move_data);
            return;
        }

        if ((can_entity_gain_level(move_data) << 16) != 0) {
            process_selected_actor_record(motion_arg, actor_index_arg, actor_arg, move_data);
        }
    }

    room_id = find_active_rect_containing_point(actor_arg->unk_24, actor_arg->unk_25);
    actor_arg->unk_26 = room_id;

    if (move_data->unk_6D > 0) {
        if (((u32)move_data->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(move_data);
            return;
        }
        if (*(u16 *)&actor_arg->unk_24 != reference_tile_object.tile_position.word) {
            if (!(move_data->unk_46 & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(move_data,
                            (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801731DC(motion_arg, actor_index_arg, actor_arg, 0) << 16) == 0) {
                    return;
                }
                action_state = move_data->unk_46 | 0x4000;
                move_data->unk_46 = action_state;
                if (!(action_state & 0x8000)) {
                    func_801726EC(motion_arg, actor_index_arg, actor_arg, move_data);
                    return;
                }
            }

            action_state = move_data->unk_46 & 0x3FFF;
            switch (action_state) {
            case 8:
                if ((initialize_directional_object(motion_arg, actor_index_arg, actor_arg, move_data) << 16) != 0) {
                    return;
                }
                update_actor_status_and_motion(motion_arg, actor_index_arg, actor_arg, move_data);
                return;

            case 10:
                if (scripted_boundary_active != 0) {
                    update_actor_status_and_mp(move_data);
                    return;
                }
                clear_high_flag_and_update_counter(motion_arg, actor_index_arg, actor_arg, move_data);
                return;

            case 9:
                if (!(((u32)move_data->flags1C) & ACTOR_PLAYER_AWARE)) {
                    update_actor_status_and_mp(move_data);
                    return;
                }
                update_actor_counter_and_status(motion_arg, actor_index_arg, actor_arg, move_data);
                return;

            case 5:
            case 6:
            case 7:
            {
                ActorRecord *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    actor_arg->unk_24, actor_arg->unk_25,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_flags);
                player = primary_actor_record;
                move_data->facing = heading;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(motion_arg, actor_index_arg, actor_arg, &baloon_attack_frames, &baloon_action_resume_address);
                    return;
                }
            }
                                        /* fallthrough */
            case 12:
                update_actor_status_and_mp(move_data);
                return;

            case 1:
            case 2:
            case 3:
                begin_actor_spell_action(motion_arg, actor_index_arg, actor_arg, &baloon_attack_frames, &baloon_action_resume_address);
                return;

            case 4:
            case 11:
            default:
                break;
            }
        }
        func_801726EC(motion_arg, actor_index_arg, actor_arg, move_data);
        return;
    }

    if (!(((u32)move_data->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) || !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)move_data->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        actor_arg->unk_24, actor_arg->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    move_data->facing = get_rounded_facing_and_rounding_flag(
                        actor_arg->unk_24, actor_arg->unk_25,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_flags);
                }
            }
        }
    }
}
