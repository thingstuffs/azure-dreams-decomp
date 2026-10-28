#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(u8, u8);
extern s32 test_neighbor_position_relation(u8, u8, u8, u8);
extern s32 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void * unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void * effect_param, void *target, u8 *direction_table, void * next_state);

void advance_queued_movement_step(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *path);
extern void func_80171BE0(void *, void *, void *, void *);
extern s32 func_80172330(void *, void *, void *, s32);
extern void func_801736B8(void *, void *, void *, void *);
extern void advance_repeated_command_stream_direction(void *, void *, void *);

extern u8 beldo_action_dispatch_address;
extern u8 beldo_frame_set_1[8];
extern u8 beldo_frame_set_2[];
extern u8 D_80173EC4[];
extern u8 D_80173EE4[];

typedef struct S_80171514_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_80171514_0;   /* arg3 in update_object_animation */

typedef struct S_80171514_3 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80171514_3;   /* entry in update_object_animation */

/* Updates object animation, dispatches its action, and adjusts its facing. */
/* Dispatches Beldo's movement and spells, replays stored commands in scripted mode, and maintains idle
 * animation and facing. */
void update_object_animation(ActorRecord *obj, ObjectPosition *motion, SpriteFrameState *part, ActorRecord *state) {
    u32 entry_status = g_dungeon_status.flags;
    s32 state_flags;
    s32 query_result;
    s32 action_kind;
    s32 jump_index;
    s32 entry_index;
    u8 *entry_base;
    u8 *entry;
    s16 distance;
    void *callback_state;

    if (entry_status & 0x1000) {
        obj->action_id.u = 14;
        advance_queued_movement_step(obj, motion, part, state);
        return;
    }

    if (((S_80171514_0 *)state)->unk_1C & 0x200) {
        if (*(u8 **)&part->frameTable == D_80173EC4) {
            obj->action_id.u = 13;
            obj->action_phase.u = 1;
            (*(u32 *)((u8 *)obj + (0x8C))) = 0;
            ((S_80171514_0 *)state)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(obj, motion, part, beldo_frame_set_2) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((S_80171514_0 *)state)->unk_1C & 0x100) {
            begin_pushed_actor_move(obj, motion, part, state);
            return;
        }

        if (obj->action_id.u != 14) {
            obj->action_id.u = 14;
        }
        if (*(u8 **)&part->frameTable != beldo_frame_set_1) {
            (part->frameTable) = beldo_frame_set_1;
            select_sprite_entry(
                part,
                beldo_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100) >> 9) & 7],
                0);
            part->frame_ticks = 1;
            obj->unk_A0.parts.high = 0;
            obj->unk_9E.s = 0;
        }

        ((S_80171514_0 *)state)->unk_1C |= 0x40000;
        obj->action_state_flags &= 0xFFF7;

        if (state->hp_delta != 0) {
            if (begin_ready_actor_directional_action(obj, motion, part, D_80173EE4) != 0) {
                return;
            }
        }

        if (((S_80171514_0 *)state)->unk_1C & 0x80000) {
            u16 previous_amount;
            u16 pending_amount;

            begin_actor_move_to_target_facing(obj, motion, part, state);
            previous_amount = (u16)obj->unk_90.parts.high.s;
            pending_amount = obj->unk_A0.parts.high;
            obj->unk_A0.parts.high = 0;
            obj->unk_9E.s = 0;
            obj->unk_90.parts.high.s = previous_amount - pending_amount;
            func_801736B8(obj, motion, part, state);
            return;
        }

        if ((s16)can_entity_gain_level(state) != 0) {
            process_selected_actor_record(obj, motion, part, state);
        }
    }

    query_result = find_active_rect_containing_point(part->tile_x, part->tile_y);
    part->room_index = query_result;

    if (state->pending_turn_updates > 0) {
        if (((S_80171514_0 *)state)->unk_1C & 0x20) {
            update_actor_status_and_mp(state);
            return;
        }

        if (*(u16 *)&part->tile_x == reference_tile_object.tile_position.word) {
            func_80171BE0(obj, motion, part, state);
            return;
        }

        if ((state->action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        state, (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }

            if (system_update_flags & 8) {
                u8 callback_flags;

                advance_repeated_command_stream_direction(obj, motion, part);
                callback_flags = state->movement_queue_state;
                callback_state = state;
                callback_flags &= 0x7F;
                state->movement_queue_state = callback_flags;
                update_actor_status_and_mp(callback_state);
                state->action_flags &= 0x7FFF;
                return;
            }

            if ((s16)func_80172330(obj, motion, part, 0) == 0) {
                return;
            }
            state->action_flags |= 0x4000;
            if ((state->action_flags & 0x8000) == 0) {
                func_80171BE0(obj, motion, part, state);
                return;
            }
        }

        action_kind = state->action_flags & 0x3FFF;
        jump_index = action_kind - 1;
        switch (jump_index) {
        case 11:
            update_actor_status_and_mp(state);
            return;

        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            callback_state = state;
            obj->unk_8C.address = &beldo_action_dispatch_address;
            update_actor_status_and_mp(callback_state);
            state->action_flags &= 0x7FFF;
            return;

        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(obj, motion, part, 0, &beldo_action_dispatch_address);
            return;

        case 3:
        case 9:
        case 10:
        default:
            func_80171BE0(obj, motion, part, state);
            return;
        }
    }

    state_flags = ((S_80171514_0 *)state)->unk_1C;
    if ((state_flags & 0x2000) == 0) {
        entry_index = (s8)query_result;
        if (entry_index >= 0) {
            entry_base = dungeon_rooms;
            entry = entry_index * 20 + entry_base;
            if (((S_80171514_3 *)entry)->unk_0C & 2) {
                return;
            }
        }
        if ((state_flags & 0x430) == 0) {
            if ((s16)test_neighbor_position_relation(
                    part->tile_x, part->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                query_result = get_rounded_facing_and_rounding_flag(
                    part->tile_x, part->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                state->facing = query_result;
            }
        }
    }
}
