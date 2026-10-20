#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(u8, u8);
extern s32 compare_monster_neighbor_values(u8, u8, u8, u8);
extern s32 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void func_80171388(void *);
extern void func_801715CC(void *, void *, void *, void *);
extern s32 attempt_actor_transition(void *, void *, void *, void *);
extern void update_action_and_directional_frame(void *, void *, void *, void *);
extern s32 func_801720E0(void *, void *, void *, s32);
extern void func_80173478(void *, void *, void *, void *);

extern u8 D_80170E68[];
extern u8 D_8017386C[];
extern u8 D_80173874[];
extern u8 D_8017389C[];

typedef struct S_80170E68_4 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80170E68_4;   /* entry in dispatch_actor_behavior_and_facing */

/* Dispatch actor behavior and update its facing animation from dungeon state. */
void dispatch_actor_behavior_and_facing(Rec_func_800A9E70_arg0 *actor, void *context, void *sprite, EntityRec *state)
{
    u16 *dungeon_status;
    s32 initial_flags;
    s32 flags;
    s32 result;
    s32 action_kind;
    s32 entry_index;
    u8 *entry_base;
    u8 *entry;
    EntityRec *player;
    s16 distance;
    u16 status_flags;

    dungeon_status = (u16 *)&g_dungeon_status.turn_scale;
    if (dungeon_status[1] & 0x1000) {
        actor->unk_9A.as_u8 = 14;
        func_80171388(actor);
        return;
    }

    if (state->tileY == 0) {
        advance_actor_pending_action(actor, context, sprite, state);
    } else {
        initial_flags = ((u32)state->flags1C);
        state->flags1C = initial_flags & -0x201;

        status_flags = dungeon_status[1];

        if ((status_flags & 0x2000) == 0) {
            if (initial_flags & 0x100) {
                begin_pushed_actor_move(actor, context, sprite, state);
                return;
            }

            if (actor->unk_9A.as_u8 != 14) {
                if (*(u8 **)((u8 *)sprite + 0x2C) != D_8017386C) {
                    *(u8 **)((u8 *)sprite + 0x2C) = D_8017386C;
                    select_sprite_entry(
                        sprite,
                        D_8017386C[((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7],
                        0);
                }
                actor->unk_9A.as_u8 = 14;
            }

            actor->unk_98 &= 0xFFF3;

            if (state->unk_64 != 0) {
                if (begin_ready_actor_directional_action(actor, context, sprite, D_80173874) != 0) {
                    return;
                }
            }

            if (((u32)state->flags1C) & 0x80000) {
                begin_actor_move_to_target_facing(actor, context, sprite, state);
                func_80173478(actor, context, sprite, state);
                return;
            }

            if ((s16)can_entity_gain_level(state) != 0) {
                process_selected_actor_record(actor, context, sprite, state);
            }
        }

        result = find_active_rect_containing_point(*(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25));
        *(u8 *)((u8 *)sprite + 0x26) = result;

        if (state->unk_6D > 0) {
            if (((u32)state->flags1C) & 0x20) {
                update_actor_status_and_food(state);
                return;
            }

            if (*(u16 *)((u8 *)sprite + 0x24) == *(u16 *)(&D_80082E80.tile_position.parts.tile_x)) {
                func_801715CC(actor, context, sprite, state);
                return;
            }

            if ((state->unk_46 & 0x8000) == 0) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((s16)check_entity_relation(state, (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                        return;
                    }
                }

                if ((s16)func_801720E0(actor, context, sprite, 0) == 0) {
                    return;
                }
                state->unk_46 |= 0x4000;
                if ((state->unk_46 & 0x8000) == 0) {
                    func_801715CC(actor, context, sprite, state);
                    return;
                }
            }

            action_kind = state->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 9:
                actor->unk_98 |= 0x8000;
                                        /* fallthrough */
            case 8:
                if ((((u32)state->flags1C) & 0x2000) &&
                    ((state->unk_46 & 0x3FFF) == 8)) {
                    actor->unk_98 &= 0x7FFF;
                }
                if ((s16)attempt_actor_transition(actor, context, sprite, state) != 0) {
                    return;
                }
                update_action_and_directional_frame(actor, context, sprite, state);
                return;

            case 5:
            case 6:
            case 7:
                result = get_rounded_facing_and_rounding_flag(
                    *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25),
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, (s16 *)&distance);
                player = D_800814A8;
                state->facing = result;
                if (player->unk_9A == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_8017389C, D_80170E68);
                    return;
                }
                                        /* fallthrough */
            case 12:
                update_actor_status_and_food(state);
                return;

            case 1:
            case 2:
            case 3:
                begin_actor_spell_action(actor, context, sprite, D_8017389C, D_80170E68);
                return;

            case 4:
            case 10:
            case 11:
            default:
                func_801715CC(actor, context, sprite, state);
                return;
            }
        }

        flags = ((u32)state->flags1C);
        if ((flags & 0x2000) == 0) {
            entry_index = (s8)result;
            if (entry_index >= 0) {
                entry_base = (u8 *)D_800E2970;
                entry = entry_base + entry_index * 20;
            }
            if (entry_index < 0 ||
                !(((S_80170E68_4 *)entry)->unk_0C & 2)) {
                if ((flags & 0x430) == 0) {
                    if ((s16)compare_monster_neighbor_values(
                            *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25),
                            D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) != 0) {
                        result = get_rounded_facing_and_rounding_flag(
                            *(u8 *)((u8 *)sprite + 0x24), *(u8 *)((u8 *)sprite + 0x25),
                            D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, (s16 *)&distance);
                        state->facing = result;
                    }
                }
            }
        }

        if (g_dungeon_status.flags & 0x2000) {
            return;
        }
        if (*(u16 *)((u8 *)sprite + 0x14) & 0x40) {
            return;
        }
    }
    if (*(u8 * *)((u8 *)sprite + 0x2C) != D_8017386C) {
        *(u8 **)((u8 *)sprite + 0x2C) = D_8017386C;
        select_sprite_entry(
            sprite,
            D_8017386C[((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7],
            0);
    }
}

