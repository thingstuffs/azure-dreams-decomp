#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/monster/hikewne.h"


extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 test_neighbor_position_relation(u8, u8, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(u8, u8, u8, u8, s16 *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);

extern void advance_actor_along_queued_path(void *, void *, SpriteFrameState *, void *);
extern s32 validate_action_and_apply_effect(void *, void *, void *, void *);
extern void clear_entity_flag_and_advance_action(void *, void *, void *, void *);
extern s32 update_entity_state_from_query(void *, void *, void *, s32);
extern void update_directional_sprite_state_and_signals(void *, void *, void *, void *);

extern u8 D_801740E0[];
#include "dungeon/monster/hikewne.h"
extern u8 D_801740F0[];
extern u8 D_80174140[];
extern u8 D_80174150[];
extern u8 D_80174158[];

typedef struct S_801714D4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
} S_801714D4_0;   /* arg0 in update_actor_behavior_animation_and_facing */

/* Updates actor behavior, animation, and facing from its status and current tile. */
void update_actor_behavior_animation_and_facing(void *actor_arg, void *context_arg, void *sprite_arg, void *stats_arg)
{
    register void *actor_head = actor_arg;
    register void *context = context_arg;
    register SpriteFrameState *sprite= sprite_arg;
    register EntityRec *stats = stats_arg;
    s16 distance;
    s32 flags;
    s32 action_index;
    s8 tile_index;
    s16 angle;
    u16 action_flags;
    void *callback;
    ActorRecord *owner;
    void *actor_tail;
#define actor_arg actor_head
#define context_arg context

    if (g_dungeon_status.flags & 0x1000) {
        ((S_801714D4_0 *)actor_arg)->unk_9A = 14;
        advance_actor_along_queued_path(actor_arg, context_arg, sprite, stats);
        return;
    }

    if (stats->tileY == 0) {
        advance_actor_pending_action(actor_arg, context_arg, sprite, stats);
        if (*(u8 **)&sprite->frameTable == D_80174158) {
            return;
        }
        (sprite->frameTable) = D_80174150;
        select_sprite_entry(
            sprite,
            D_80174150[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)stats->flags1C) & 0x200) {
        if (*(u8 **)&sprite->frameTable == D_80174158) {
            ((S_801714D4_0 *)actor_arg)->unk_9A = 13;
            ((S_801714D4_0 *)actor_arg)->unk_9B = 1;
            ((S_801714D4_0 *)actor_arg)->unk_8C = 0;
            stats->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor_arg, context_arg, sprite, D_801740F0) != 0) {
            return;
        }
    }

    if ((g_dungeon_status.flags & 0x2000) == 0) {
        if (((u32)stats->flags1C) & 0x100) {
            begin_pushed_actor_move(actor_arg, context_arg, sprite, stats);
            return;
        }

        if (((S_801714D4_0 *)actor_arg)->unk_9A != 14) {
            ((S_801714D4_0 *)actor_arg)->unk_9A = 14;
        }

        if ((*(u8 **)&sprite->frameTable != D_801740E0) &&
            (*(u8 **)&sprite->frameTable != hikewne_alt_direction_frames)) {
            (sprite->frameTable) = D_801740E0;
            select_sprite_entry(
                sprite,
                D_801740E0[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                0);
            sprite->unk_05 = 1;
            ((S_801714D4_0 *)actor_arg)->unk_A2.s = 0;
            ((S_801714D4_0 *)actor_arg)->unk_9E = 0;
        }

        stats->flags1C |= 0x40000;
        ((S_801714D4_0 *)actor_arg)->unk_98 &= 0xFFF7;

        if (stats->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_arg, context_arg, sprite, D_80174140) != 0) {
                return;
            }
        }

        if (((u32)stats->flags1C) & 0x80000) {
            begin_actor_move_to_target_facing(actor_arg, context_arg, sprite, stats);
            ((S_801714D4_0 *)actor_arg)->unk_92 -= ((S_801714D4_0 *)actor_arg)->unk_A2.u;
            ((S_801714D4_0 *)actor_arg)->unk_A2.s = 0;
            ((S_801714D4_0 *)actor_arg)->unk_9E = 0;
            update_directional_sprite_state_and_signals(actor_arg, context_arg, sprite, stats);
            return;
        }

        if ((s16)can_entity_gain_level(stats) != 0) {
            process_selected_actor_record(actor_arg, context_arg, sprite, stats);
        }
    }

    actor_tail = actor_head;
#undef actor_arg
#define actor_arg actor_tail
    tile_index = find_active_rect_containing_point(sprite->unk_24, sprite->unk_25);
    sprite->unk_26 = tile_index;

    if (stats->unk_6D > 0) {
        if (((u32)stats->flags1C) & 0x20) {
            update_actor_status_and_mp(stats);
            return;
        }
        if (*(u16 *)&sprite->unk_24 == reference_tile_object.tile_position.word) {
            select_movement_direction_and_advance(actor_arg, context_arg, sprite, stats);
            return;
        }
        action_flags = stats->unk_46;
        if ((action_flags & 0x8000) == 0) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((s16)check_entity_relation(
                        stats, (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)update_entity_state_from_query(actor_arg, context_arg, sprite, 0) == 0) {
                return;
            }
            action_flags = stats->unk_46 | 0x4000;
            stats->unk_46 = action_flags;
            if ((action_flags & 0x8000) == 0) {
                select_movement_direction_and_advance(actor_arg, context_arg, sprite, stats);
                return;
            }
        }

        action_index = (stats->unk_46 & 0x3FFF) - 1;
        switch (action_index) {
        case 7:
        case 8:
        case 9:
            if ((s16)validate_action_and_apply_effect(actor_arg, context_arg, sprite, stats) != 0) {
                return;
            }
            clear_entity_flag_and_advance_action(actor_arg, context_arg, sprite, stats);
            return;

        case 4:
        case 5:
        case 6:
            angle = get_rounded_facing_and_rounding_flag(
                sprite->unk_24, sprite->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
            owner = primary_actor_record;
            stats->facing = angle;
            if (owner->unk_9A == 0x11) {
                callback = (void *)update_actor_behavior_animation_and_facing;
                begin_actor_spell_action(actor_arg, context_arg, sprite, 0, callback);
                return;
            }

        case 11:
            update_actor_status_and_mp(stats);
            return;

        case 0:
        case 1:
        case 2:
            callback = (void *)update_actor_behavior_animation_and_facing;

            begin_actor_spell_action(actor_arg, context_arg, sprite, 0, callback);
            return;

        default:
            select_movement_direction_and_advance(actor_arg, context_arg, sprite, stats);
            return;
        }
    }

    flags = ((u32)stats->flags1C);
    if (flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (dungeon_rooms[tile_index].flags & 2) {
            return;
        }
    }
    if (flags & 0x430) {
        return;
    }

    {

        if ((s16)test_neighbor_position_relation(
                sprite->unk_24, sprite->unk_25,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) == 0) {
            return;
        }
        stats->facing = get_rounded_facing_and_rounding_flag(
            sprite->unk_24, sprite->unk_25,
            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &distance);
    }
#undef actor_arg
#undef context_arg
}
