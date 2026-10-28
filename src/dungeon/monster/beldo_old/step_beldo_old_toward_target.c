#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/actor_status.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "dungeon/level/room_flags.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_8127C3E0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8127C3E0_0;   /* global in step_beldo_old_toward_target */

typedef struct S_8127C3E0_6 {
    u8 pad_00[0x8];
    u16 unk_08;
} S_8127C3E0_6;   /* global_count in step_beldo_old_toward_target */

extern s32 func_80171328(void *, void *, void *, void *);
extern void func_800A86C4(void *);
extern void func_800A06B4(void *, void *, s32, s32, void *);
extern void *func_8009F09C(void *, u8, u8);
extern s16 func_8009F608(s32, s32, s32, s32, void *);
extern s32 func_800A59E8(void);
extern void *func_8009F2E0(void *, u8, u8, s16);
extern s16 func_8009EF24(void *, void *);
extern s16 func_80099330(s32, s32, s32, s16);
extern s16 func_8009EB6C(s32, s32, s32, s32);
extern void find_active_rect_containing_point(void *, s8, void *, void *);
extern s16 func_800996B0(s16, void *, void *, s32);
extern void initialize_indexed_object_and_lookup_value(s32, s32, s32);
extern void func_8009900C(s32, s32, s32);
extern s16 func_80098F70(void *, void *);
extern s16 func_800BB784(s32, s32, s16);

extern s8 D_8006BDA8;
extern s8 D_8006BDB8;
extern s16 beldo_turn_angle_steps[];
extern ActorRecord *beldo_old_target_actor;   /* the primary actor pointer in this build */
extern u8 free_node_list_head[];
extern s8 cd_queue_buffered_argument_word_1;
extern s32 D_80085990;
extern DungeonRoom D_800E1D50[];   /* this build's room table */

/* Updates an actor's movement direction, position, and remaining path steps. */
void step_beldo_old_toward_target(Rec_func_800A9E70_arg0 *move_state_arg, void *action_context, SpriteFrameState *position_arg, ActorRecord *actor_arg)
{
    S_8127C3E0_0 *dungeon_state = (S_8127C3E0_0 *)&D_80085990;
    u16 dungeon_flags = dungeon_state->unk_02;
    s32 limit_detour = 0;
    s16 detour_test;
    s32 actor_flags;
    s32 trial_angle;
    s32 current_angle;   /* also receives the blocker lookups below: retail keeps them in one register */
    u16 turn_flags;
    s16 turn_index;
    s16 *turn_table;
    s32 step_offset;
    ActorRecord *blocker;

    if ((dungeon_flags & 0x4000) || (s8)actor_arg->movement_queue_state >= 0) {
        if (actor_arg->unk_12 >= 2 ||
            (s16)func_80171328(move_state_arg, action_context, position_arg, actor_arg) == 0) {
            func_800A86C4(actor_arg);
            return;
        }
        if (dungeon_state->unk_0C == actor_arg) {
            actor_arg->action_flags = 0xC008;
        }
        return;
    }
    if (!(dungeon_flags & 0x2000)) {
        return;
    }

    func_800A06B4(position_arg, actor_arg, 3, 6, &move_state_arg->unk_9C.as_s8);
    actor_flags = actor_arg->flags1C;
    if (actor_flags & 0x410) {
        if (actor_flags & 0x400) {
            current_angle = (s32)func_8009F09C(actor_arg, position_arg->tile_x,
                                  position_arg->tile_y);
            blocker = (ActorRecord *)current_angle;
            if (blocker != 0) {
                SpriteFrameState *blocker_sprite = ((ObjectNodeHeader *)blocker - 1)->sprite;
                s16 target_angle = func_8009F608(
                    position_arg->tile_x, position_arg->tile_y,
                    blocker_sprite->tile_x,
                    blocker_sprite->tile_y,
                    &move_state_arg->unk_98);
                actor_arg->facing = target_angle;
                actor_arg->movement_queue_state &= 0x7F;
                return;
            }
            if (!(actor_arg->flags14 & 0x80000000)) {
                actor_arg->flags14 |= 0x80000000;
                actor_arg->facing +=
                    (func_800A59E8() & 7) << 9;
            }
        } else {
            if (func_8009F2E0(actor_arg, position_arg->tile_x,
                              position_arg->tile_y,
                              actor_arg->facing) != 0) {
                actor_arg->movement_queue_state &= 0x7F;
                return;
            }
        }
    } else if (actor_flags & 0x2000) {
        if (!(actor_arg->action_flags & ACTOR_ACTION_PENDING)) {
            if (actor_flags & 0x20000) {
                s16 target_angle;
                s32 target_x;
                s32 target_y;
                u16 *turn_state;
                {
                    u8 *target_position = free_node_list_head;
                    s32 target_facing = (u16)beldo_old_target_actor->facing;
                    s32 direction_offset =
                        ((((u8 *)&actor_arg->unk_44)[1] + ((s16)target_facing >> 9)) & 7) << 1;
                    target_x = target_position[0x24] +
                        *(u16 *)((u8 *)&D_8006BDA8 + direction_offset);
                    target_y = target_position[0x25] +
                        *(u16 *)((u8 *)&D_8006BDB8 + direction_offset);
                }

                if (position_arg->tile_x == (u16)target_x &&
                    position_arg->tile_y == (u16)target_y) {
                    actor_arg->movement_queue_state &= 0x7F;
                    return;
                }

                turn_state = &move_state_arg->unk_98;
                target_angle = func_8009F608(
                    position_arg->tile_x, position_arg->tile_y,
                    (s16)target_x, (s16)target_y, turn_state);
                actor_arg->facing = target_angle;
                if (func_800996B0(target_angle, position_arg, actor_arg, 0x20) <= 0) {
                    actor_arg->facing = func_8009F608(
                        position_arg->tile_x, position_arg->tile_y,
                        free_node_list_head[0x24], free_node_list_head[0x25], turn_state);
                }
                if (func_8009EB6C(
                        position_arg->tile_x, position_arg->tile_y,
                        free_node_list_head[0x24], free_node_list_head[0x25]) != 0) {
                    limit_detour = 1;
                }
            } else {
                find_active_rect_containing_point(position_arg, move_state_arg->unk_9C.as_s8, actor_arg,
                              &move_state_arg->unk_98);
            }
        }
    } else if ((s8)position_arg->room_index >= 0 &&
               D_800E1D50[(s8)position_arg->room_index].flags & ROOM_HOLY_BEAM) {
        find_active_rect_containing_point(position_arg, move_state_arg->unk_9C.as_s8, actor_arg,
                      &move_state_arg->unk_98);
    } else if (!(actor_arg->action_flags & ACTOR_ACTION_PENDING)) {
        current_angle = (s32)func_8009F2E0(actor_arg, position_arg->tile_x,
                              position_arg->tile_y,
                              actor_arg->facing);
        blocker = (ActorRecord *)current_angle;
        if (blocker != 0 &&
            (blocker->flags1C & ACTOR_PLAYER_SIDE) &&
            (s16)func_8009EF24(blocker, actor_arg) < 0x81) {
            if (func_80099330(
                    (actor_arg->facing >> 9) & 0xFFFF,
                    position_arg->tile_x, position_arg->tile_y,
                    (s16)(actor_arg->ground_height - 0x20)) != 0) {
                actor_arg->movement_queue_state &= 0x7F;
                return;
            }
        }

        if (actor_arg->flags1C & ACTOR_PLAYER_AWARE) {
            u8 *target_position = free_node_list_head;
            actor_arg->facing = func_8009F608(
                position_arg->tile_x, position_arg->tile_y,
                target_position[0x24], target_position[0x25], &move_state_arg->unk_98);
            if (func_8009EB6C(
                    position_arg->tile_x, position_arg->tile_y,
                    target_position[0x24], target_position[0x25]) != 0) {
                if ((s16)func_8009EF24(beldo_old_target_actor, actor_arg) < 0x81) {
                    if (func_80099330(
                            (actor_arg->facing >> 9) & 0xFFFF,
                            position_arg->tile_x,
                                position_arg->tile_y,
                            (s16)(actor_arg->ground_height - 0x20)) != 0) {
                        actor_arg->movement_queue_state &= 0x7F;
                        return;
                    }
                }
            }
        } else {
            find_active_rect_containing_point(position_arg, move_state_arg->unk_9C.as_s8, actor_arg,
                          &move_state_arg->unk_98);
        }
    }

    turn_index = -1;

    while (++turn_index < 8) {
        turn_flags = move_state_arg->unk_98;
        current_angle = actor_arg->facing;
        if (turn_flags & 2) {
            trial_angle = current_angle - beldo_turn_angle_steps[turn_index];
        } else {
            trial_angle = current_angle + beldo_turn_angle_steps[turn_index];
        }

        if (func_800996B0(trial_angle, position_arg, actor_arg, 0x20) > 0) {
            if (turn_index >= 3) {
                detour_test = limit_detour;
                if (detour_test != 0) {
                    actor_arg->movement_queue_state &= 0x7F;
                    return;
                }
            }

            actor_arg->facing = trial_angle;
            ((ActorStatusBytesView *)((u8 *)actor_arg + (actor_arg->movement_queue_state & 0x7F)))->path_x =
                position_arg->tile_x;
            ((ActorStatusBytesView *)((u8 *)actor_arg + (actor_arg->movement_queue_state & 0x7F)))->path_y =
                position_arg->tile_y;
            actor_arg->movement_queue_state++;

            initialize_indexed_object_and_lookup_value(
                position_arg->tile_x, position_arg->tile_y,
                (actor_arg->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);

            {
                u8 *x_step;

                x_step = (u8 *)&D_8006BDA8;
                step_offset = ((u16)actor_arg->facing >> 8) & 0xE;
                x_step += step_offset;
                position_arg->tile_x += *x_step;
                position_arg->tile_y += *((u8 *)&D_8006BDB8 + step_offset);
            }

            func_8009900C(
                position_arg->tile_x, position_arg->tile_y,
                (actor_arg->flags1C & ACTOR_PLAYER_SIDE) ? 0x300 : 0x3000);
            break;
        }

        if (turn_index == 0 &&
            *(u16 *)&cd_queue_buffered_argument_word_1 != *(u16 *)&position_arg->tile_x) {
            if (func_80098F70(actor_arg,
                    (u8 *)beldo_old_target_actor->previous_actor_header + 0x20) != 0) {
                return;
            }
        }

    }

    if (turn_index >= 8) {
        actor_arg->movement_queue_state &= 0x7F;
        actor_arg->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        func_800A86C4(actor_arg);
        return;
    }

    {
        S_8127C3E0_6 *dungeon_counts = (S_8127C3E0_6 *)&D_80085990;
        actor_arg->action_flags &= ACTOR_ACTION_CLEAR_PENDING_MASK;
        move_state_arg->unk_9C.as_u8 = position_arg->room_index;
        actor_arg->pending_turn_updates--;
        dungeon_counts->unk_08++;
    }
    if (actor_arg->pending_turn_updates == 0) {
        actor_arg->movement_queue_state &= 0x7F;
        return;
    }

    turn_index = func_800BB784(
        (position_arg->tile_x << 6) | 0x20,
        (position_arg->tile_y << 6) | 0x20,
        (s16)(actor_arg->ground_height - 0x20));
    if (turn_index < 0x200) {
        actor_arg->ground_height = turn_index;
    }
}
