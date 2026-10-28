#include "shared/object_node.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_80171094_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    union { s16 s; u16 u; } unk_A6;   /* accessed as both */
    u8 pad_A8[0x4];
    union { s16 s; u16 u; } unk_AC;   /* accessed as both */
} S_80171094_0;   /* arg0 in update_actor_animation */

typedef struct S_80171094_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171094_1;   /* arg3 in update_actor_animation */

extern void select_sprite_entry(void *, u8, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 test_neighbor_position_relation(u8, u8, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);

extern void advance_path_motion(void *, ObjectPosition *, SpriteFrameState *, void *);
extern void func_801718B4(void *, void *, void *, void *);
extern s32 func_80171FFC(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);
void finish_actor_tile_move_and_check_trap(ActorRecord *action_state, ObjectPosition *action_ctx, SpriteFrameState *sprite, ActorRecord *actor);
s32 search_ahead_and_start_action(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
void update_action_state_direction_specific(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *sprite, ActorRecord *actor);
void clear_actor_action_flag_and_animate(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *animation, ActorRecord *actor);

extern s32 func_80172A5C(void *, void *, void *, s32);
extern void func_80174520(void *, void *, void *, void *);

extern u8 cyclone_move_direction_frames[];
extern u8 D_80176468[];
#include "dungeon/monster/cyclone.h"
extern u8 D_801764A8[];

/* Updates actor animation, status, and behavior according to dungeon state. */
void update_actor_animation(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg) {
    void *stats = stats_arg;
    s16 distance;
    s8 tile_id;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        actor_arg->action_id.u = 14;
        advance_path_motion(actor_arg, context_arg, sprite_arg, stats);
        return;
    }

    if (((S_80171094_1 *)stats)->unk_25 == 0) {
        advance_actor_pending_action(actor_arg, context_arg, sprite_arg, stats);
        if (*(u8 **)&sprite_arg->frameTable == cyclone_direction_frames) {
            return;
        }
        {
            u8 *animations = D_80176468;
            (sprite_arg->frameTable) = animations;
            select_sprite_entry(
                sprite_arg,
                animations[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80171094_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171094_1 *)stats)->unk_1C & 0x200) {
        if (*(u8 **)&sprite_arg->frameTable == cyclone_direction_frames) {
            actor_arg->action_id.u = 13;
            actor_arg->action_phase.u = 1;
            ((S_80171094_0 *)actor_arg)->unk_8C = 0;
            ((S_80171094_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, sprite_arg, D_80176468) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((S_80171094_1 *)stats)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor_arg, context_arg, sprite_arg, stats);
            return;
        }

        if (actor_arg->action_id.u != 14) {
            actor_arg->action_id.u = 14;
        }

        if (*(u8 **)&sprite_arg->frameTable != cyclone_move_direction_frames) {
            u8 *animations = cyclone_move_direction_frames;
            (sprite_arg->frameTable) = animations;
            select_sprite_entry(
                sprite_arg,
                animations[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80171094_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            sprite_arg->frame_ticks = 1;
            ((S_80171094_0 *)actor_arg)->unk_A6.s = 0;
            ((S_80171094_0 *)actor_arg)->unk_AC.s = 0;
        }

        {
            u32 flags = ((S_80171094_1 *)stats)->unk_1C;
            u16 actor_flags;

            if (flags & 0x20) {
                ((S_80171094_1 *)stats)->unk_1C = flags & ~0x40000;
                actor_flags = actor_arg->action_state_flags | 8;
            } else {
                ((S_80171094_1 *)stats)->unk_1C = flags | 0x40000;
                actor_flags = actor_arg->action_state_flags & 0xFFF7;
            }
            actor_arg->action_state_flags = actor_flags;
        }

        if (((S_80171094_1 *)stats)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, sprite_arg, D_801764A8) != 0) {
                return;
            }
        }

        if (((S_80171094_1 *)stats)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, sprite_arg, stats);
            actor_arg->unk_90.parts.high.u -= ((S_80171094_0 *)actor_arg)->unk_A6.u;
            ((S_80171094_0 *)actor_arg)->unk_A6.u = 0;
            ((S_80171094_0 *)actor_arg)->unk_AC.u = 0;
            func_80174520(actor_arg, context_arg, sprite_arg, stats);
            return;
        }

        if ((s16)can_entity_gain_level(stats) != 0) {
            process_selected_actor_record(actor_arg, context_arg, sprite_arg, stats);
        }
    }

    tile_id = find_active_rect_containing_point(sprite_arg->tile_x, sprite_arg->tile_y);
    sprite_arg->room_index = tile_id;

    if (((S_80171094_1 *)stats)->unk_6D > 0) {
        if (((S_80171094_1 *)stats)->unk_1C & 0x20) {
            update_actor_status_and_mp(stats);
            return;
        }
        if (*(u16 *)&sprite_arg->tile_x == reference_tile_object.tile_position.word) {
            func_801718B4(actor_arg, context_arg, sprite_arg, stats);
            return;
        }
        action_flags = ((S_80171094_1 *)stats)->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((s16)check_entity_relation(
                            stats, previous_actor) != 0) {
                        return;
                    }
                }
            }
            if ((s16)func_80172A5C(actor_arg, context_arg, sprite_arg, 0) == 0) {
                return;
            }
            action_flags = ((S_80171094_1 *)stats)->unk_46 | 0x4000;
            ((S_80171094_1 *)stats)->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                func_801718B4(actor_arg, context_arg, sprite_arg, stats);
            return;
            }
        }

        switch (((S_80171094_1 *)stats)->unk_46 & 0x3FFF) {
        case 8:
            if ((s16)func_80171FFC(actor_arg, context_arg, sprite_arg, stats) != 0) {
                return;
            }
            finish_actor_tile_move_and_check_trap(actor_arg, context_arg, sprite_arg, stats);
            return;
        case 9:
            if (((S_80171094_1 *)stats)->unk_1C & 0x400) {
                s32 behavior_state;
                behavior_state = ((S_80171094_1 *)stats)->unk_14;
                if ((behavior_state & 0x80000000) == 0) {
                    behavior_state |= 0x80000000;
                    ((S_80171094_1 *)stats)->unk_14 = behavior_state;
                    ((S_80171094_1 *)stats)->unk_2A.u += (generate_random_value() & 7) << 9;
                }
            }
            switch ((s16)search_ahead_and_start_action(actor_arg, context_arg, sprite_arg, stats)) {
            case -1:
            case 1:
                break;
            case 0:
                update_action_state_direction_specific(actor_arg, context_arg, sprite_arg, stats);
                return;
            case 2:
                clear_actor_action_flag_and_animate(actor_arg, context_arg, sprite_arg, stats);
                return;
            case 3:
                attempt_actor_directional_action(actor_arg, context_arg, sprite_arg, stats);
                return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                s16 heading = get_rounded_facing_and_rounding_flag(
                    sprite_arg->tile_x, sprite_arg->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
                ActorRecord *player = primary_actor_record;
                ((S_80171094_1 *)stats)->unk_2A.s = heading;
                if (player->action_id.u == 0x11) {
                    begin_actor_spell_action(actor_arg, context_arg, sprite_arg, cyclone_move_direction_frames, update_actor_animation);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(stats);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor_arg, context_arg, sprite_arg, cyclone_move_direction_frames, update_actor_animation);
            return;
        default:
            func_801718B4(actor_arg, context_arg, sprite_arg, stats);
            return;
        }
    }

    {
        u32 flags = ((S_80171094_1 *)stats)->unk_1C;

        if (!(flags & 0x2000)) {
            s32 tile_index = (s8)tile_id;

            if ((tile_index < 0) ||
                !(dungeon_rooms[tile_index].flags & 2)) {
                if (!(flags & 0x430)) {
                    if ((s16)test_neighbor_position_relation(
                            sprite_arg->tile_x, sprite_arg->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                        ((S_80171094_1 *)stats)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                            sprite_arg->tile_x, sprite_arg->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                            &distance);
                    }
                }
            }
        }
    }
}
