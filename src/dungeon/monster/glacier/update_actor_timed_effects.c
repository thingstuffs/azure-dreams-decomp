#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

extern void select_record_entry_and_value(void *, void *, s32);
extern s32 resolve_record_orientation_or_fallback(void *, void *, void *, s32);
extern void select_sprite_entry(void *, s32, s32);
extern void advance_sprite_animation_and_textures(void *);
extern s32 rand(void);
extern s32 check_entity_relation(void *, void *);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, void *, void *, void *);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *, void *, void *, void *, void *);
extern void initialize_object_rendering_and_params(void *, void *, void *);
extern void func_80171C3C(void *, void *, void *, void *);
extern void func_80171E80(void *, void *, void *, void *);
extern s32 func_8017263C(void *, void *, void *, void *);
extern void func_80172800(void *, void *, void *, void *);
extern s32 func_80172918(void *, void *, void *, s32);
extern void func_8017412C(void *, void *, void *, void *);
extern void func_801756E0(void *, void *, void *, void *);

extern u8 secondary_sprite[];
extern void *D_80170808[];
extern u8 D_80170A0C[];

#include "dungeon/monster/glacier.h"
extern u8 glacier_frame_set_1[];
extern u8 D_801760AC[];
extern u8 D_801760DC[];
extern u8 D_801760E4[];
extern u8 glacier_frame_set_2[];

typedef struct S_801714B8_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801714B8_0_pre;   /* the 0x14 bytes before arg0 in update_actor_timed_effects, addressed as arg0[-1] */

typedef struct S_801714B8_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    union { s16 s; u16 u; } unk_9E;   /* accessed as both */
    s16 unk_A0;
} S_801714B8_0;   /* arg0 in update_actor_timed_effects */

typedef struct S_801714B8_1 {
    u8 pad_00[0x1C];
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
} S_801714B8_1;   /* arg3 in update_actor_timed_effects */
typedef struct S_801714B8_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u8 pad_1E[0xA];
    void * unk_28;
} S_801714B8_7;   /* object_data in update_actor_timed_effects */

typedef struct S_801714B8_8 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801714B8_8;   /* owner in update_actor_timed_effects */

/* Updates actor behavior, facing, and timed animation effects in the dungeon. */
/* Dispatches Glacier's movement, attacks, spells, and turn processing, adding timed idle gestures and an
 * attached effect. */
void update_actor_timed_effects(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg) {
    void *actor;
    void *context;
    SpriteFrameState *sprite;
    void *stats;
    s32 room_id;
    u16 distance;
    u16 spawn_offset[3];
    u32 initial_flags = g_dungeon_status.flags;

    actor = actor_arg;
    context = context_arg;
    sprite = sprite_arg;
    stats = stats_arg;

    if (initial_flags & 0x1000) {
        ((S_801714B8_0 *)actor)->unk_9A = 0xE;
        func_80171C3C(actor, context, sprite, stats);
        return;
    }

    if (((S_801714B8_1 *)stats)->unk_25 == 0) {
        advance_actor_pending_action(actor, context, sprite, stats);
        if (sprite->frameTable != glacier_frame_set_2) {
            u8 *state_table = D_801760E4;

            (sprite->frameTable) = state_table;
            select_sprite_entry(sprite,
                state_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((S_801714B8_1 *)stats)->unk_1C & 0x200) {
        if (sprite->frameTable == glacier_frame_set_2) {
            ((S_801714B8_0 *)actor)->unk_9A = 0xD;
            ((S_801714B8_0 *)actor)->unk_9B = 1;
            ((S_801714B8_0 *)actor)->unk_8C = 0;
            ((S_801714B8_1 *)stats)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_801760E4)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_801714B8_1 *)stats)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, stats);
            return;
        }

        if (((S_801714B8_0 *)actor)->unk_9A != 0xE) {
            u8 state = 0xE;
            u8 *state_table = glacier_direction_frames;

            if (sprite->frameTable != state_table) {
                (sprite->frameTable) = state_table;
                select_sprite_entry(sprite,
                    state_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
            }
            ((S_801714B8_0 *)actor)->unk_9E.s = 0;
            ((S_801714B8_0 *)actor)->unk_A0 = (rand() & 0x1F) + 0xF;
            ((S_801714B8_0 *)actor)->unk_9A = state;
        }

        ((S_801714B8_0 *)actor)->unk_98 &= 0xFFF3;
        if (((S_801714B8_1 *)stats)->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_801760AC)) {
                return;
            }
        }

        if (((S_801714B8_1 *)stats)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite, stats);
            func_8017412C(actor, context, sprite, stats);
            return;
        }

        if ((s16)can_entity_gain_level(stats) != 0) {
            process_selected_actor_record(actor, context, sprite, stats);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (((S_801714B8_1 *)stats)->unk_6D > 0) {
        if (!(((S_801714B8_1 *)stats)->unk_1C & 0x20)) {
            if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
                func_80171E80(actor, context, sprite, stats);
                return;
            }
            if (!(((S_801714B8_1 *)stats)->unk_46 & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((s16)check_entity_relation(stats,
                            (u8 *)primary_actor_record->previous_actor_header + 0x20) != 0) {
                        return;
                    }
                }
                if ((s16)func_80172918(actor, context, sprite, 0) == 0) {
                    return;
                }
                ((S_801714B8_1 *)stats)->unk_46 |= 0x4000;
                if (!(((S_801714B8_1 *)stats)->unk_46 & 0x8000)) {
                    func_80171E80(actor, context, sprite, stats);
                    return;
                }
            }

            switch (((S_801714B8_1 *)stats)->unk_46 & 0x3FFF) {
            case 8:
                if ((s16)func_8017263C(actor, context, sprite, stats) == 0) {
                    func_80172800(actor, context, sprite, stats);
                    return;
                }
                return;

            case 9:
                func_801756E0(actor, context, sprite, stats);
                return;

            case 5:
            case 6:
            case 7:
            {
                ActorRecord *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                ((S_801714B8_1 *)stats)->unk_2A.s = heading;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_801760DC, update_actor_timed_effects);
                    return;
                }
                break;
            }
            case 1:
            case 2:
            case 3:
                goto aaf_cleanup;
            case 12:
                break;
            default:
                goto ordinary_cleanup;
            }
        }
special_cleanup:
        update_actor_status_and_mp(stats);
        return;

aaf_cleanup:
        begin_actor_spell_action(actor, context, sprite, D_801760DC, update_actor_timed_effects);
        return;

ordinary_cleanup:
        func_80171E80(actor, context, sprite, stats);
        return;
    } else if (!(((S_801714B8_1 *)stats)->unk_1C & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((S_801714B8_1 *)stats)->unk_1C & 0x430)) {

                if ((s16)test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    ((S_801714B8_1 *)stats)->unk_2A.s = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }

    if (g_dungeon_status.flags & 0x2000) {
        return;
    }
    if (sprite->flags & 0x40) {
        return;
    }
    if (((S_801714B8_1 *)stats)->unk_1C & 0x20) {
        return;
    }

    {
        u8 *main_table = glacier_direction_frames;

        if (sprite->frameTable != main_table) {
            if (sprite->frameTable != glacier_frame_set_1) {
                (sprite->frameTable) = main_table;
                select_sprite_entry(sprite,
                    main_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                ((S_801714B8_0 *)actor)->unk_9E.s = 0;
                ((S_801714B8_0 *)actor)->unk_A0 = (rand() & 0x1F) + 0xF;
            }
        }

        if (sprite->frameTable == main_table) {
            s16 idle_timer = ((S_801714B8_0 *)actor)->unk_9E.u;

            ((S_801714B8_0 *)actor)->unk_9E.u = idle_timer + 1;
            if (idle_timer >= ((S_801714B8_0 *)actor)->unk_A0) {
                ObjectNodeHeader *object;
                u8 *object_data;

                u8 *alt_table = glacier_frame_set_1;

                (sprite->frameTable) = alt_table;
                select_sprite_entry(sprite,
                    alt_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
                    0);
                advance_sprite_animation_and_textures(sprite);

                /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_8102FCB8). */
                do {
                    object = allocate_flagged_object_node(0x212);
                } while (0);
                if (object != 0) {
                    initialize_object_rendering_and_params(object, actor, context);
                    object->update_callback = D_80170A0C;
                    object_data = (u8 *)object + 0x20;
                    ((S_801714B8_7 *)object_data)->unk_28 = context;
                    ((S_801714B8_7 *)object_data)->unk_1C = ((S_801714B8_1 *)stats)->unk_2A.u;

                    {
                        void *owner = ((S_801714B8_0_pre *)actor)[-1].unk_00;

                        if (resolve_record_orientation_or_fallback(
                                ((S_801714B8_8 *)owner)->unk_08, owner, spawn_offset, 0xF)) {
                            void *part = object->position;

                            *(u16 *)&((ObjectPosition *)part)->x.w.i += spawn_offset[0];
                            *(u16 *)&((ObjectPosition *)part)->y.w.i += spawn_offset[1];
                            *(u16 *)&((ObjectPosition *)part)->z.w.i += spawn_offset[2];
                        }
                    }
                    {
                        void *part = object->sprite;
                        ((SpriteFrameState *)part)->flags |= 0x80;
                        select_record_entry_and_value(part, &secondary_sprite, 0);
                    }
                }
            }
        }
    }

    if (sprite->frameTable == glacier_frame_set_1 &&
        (sprite->flags & 0x6000)) {
        u8 *state_table = glacier_direction_frames;

        (sprite->frameTable) = state_table;
        select_sprite_entry(sprite,
            state_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801714B8_1 *)stats)->unk_2A.s + 0x100) >> 9) & 7],
            0);
        ((S_801714B8_0 *)actor)->unk_9E.s = 0;
        ((S_801714B8_0 *)actor)->unk_A0 = (rand() & 0x1F) + 0xF;
    }
}
