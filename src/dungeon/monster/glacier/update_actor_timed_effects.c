#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_sprite_data.h"
#include "common.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon/monster/glacier/projected_depth.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/scene.h"
#include "engine/graphics.h"
#include "dungeon/item.h"
#include "slus.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
#include "sdk/libc.h"




#include "dungeon/monster/dragon/transition_effect.h"
#include "dungeon/monster/grineut/path_motion.h"
#include "dungeon/item/find_active_rect_containing_point_api.h"

extern void initialize_object_rendering_and_params(ObjectNodeHeader *, void *, ObjectPosition *);
extern void choose_block_move_slot_a(void *, void *, void *, void *);
extern void func_8017412C(void *, void *, void *, void *);
extern void clear_actor_flag_and_apply_effect(ActorRecord *action_state, ObjectPosition *effect_arg, SpriteFrameState *anim_state, ActorRecord *actor);

extern u8 D_80170A0C[];

#include "dungeon/monster/glacier.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"
#include "dungeon/monster/glacier_frames.h"

extern u8 D_801760AC[];
extern u8 D_801760DC[];
extern u8 D_801760E4[];

typedef struct S_801714B8_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801714B8_0_pre;   /* the 0x14 bytes before arg0 in update_actor_timed_effects, addressed as arg0[-1] */



/* Updates actor behavior, facing, and timed animation effects in the dungeon. */
/* Dispatches Glacier's movement, attacks, spells, and turn processing, adding timed idle gestures and an
 * attached effect. */
void update_actor_timed_effects(ActorRecord *actor_arg, ObjectPosition *context_arg, SpriteFrameState *sprite_arg, ActorRecord *stats_arg) {
    ActorRecord *actor;
    void *context;
    SpriteFrameState *sprite;
    ActorRecord *stats;
    s32 room_id;
    u16 distance;
    GteOffset spawn_offset;
    u32 initial_flags = g_dungeon_status.flags;

    actor = actor_arg;
    context = context_arg;
    sprite = sprite_arg;
    stats = stats_arg;

    if (initial_flags & 0x1000) {
        actor->action_id = 0xE;
        advance_stored_path_motion(actor, context, sprite, stats);
        return;
    }

    if (stats->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, stats);
        if (sprite->frameTable != glacier_frame_set_2) {
            u8 *state_table = D_801760E4;

            (sprite->frameTable) = state_table;
            select_sprite_entry(sprite,
                state_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                0);
            return;
        }
        return;
    }

    if (((u32)stats->flags1C) & 0x200) {
        if (sprite->frameTable == glacier_frame_set_2) {
            actor->action_id = 0xD;
            actor->action_phase = 1;
            actor->unk_8C.word = 0;
            stats->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_801760E4)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)stats->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, stats);
            return;
        }

        if (actor->action_id != 0xE) {
            u8 state = 0xE;
            u8 *state_table = glacier_direction_frames;

            if (sprite->frameTable != state_table) {
                (sprite->frameTable) = state_table;
                select_sprite_entry(sprite,
                    state_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->unk_9E = 0;
            actor->unk_A0.parts.low = (rand() & 0x1F) + 0xF;
            actor->action_id = state;
        }

        actor->action_state_flags &= 0xFFF3;
        if (stats->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_801760AC)) {
                return;
            }
        }

        if (((u32)stats->flags1C) & 0x80000) {
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

    if (stats->pending_turn_updates > 0) {
        if (!(((u32)stats->flags1C) & 0x20)) {
            if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
                choose_block_move_slot_a(actor, context, sprite, stats);
                return;
            }
            if (!(stats->action_flags & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    {
                        ObjectNodeHeader *previous_node;
                        void *previous_body;
                        ActorRecord *previous_actor;

                        previous_node = primary_actor_record->previous_actor_header;
                        previous_body = NODE_BODY(previous_node);
                        previous_actor = previous_body;
                        if ((s16)check_entity_relation(stats,
                                previous_actor) != 0) {
                            return;
                        }
                    }
                }
                if ((s16)update_entity_state_from_query(actor, context, sprite, 0) == 0) {
                    return;
                }
                stats->action_flags |= 0x4000;
                if (!(stats->action_flags & 0x8000)) {
                    choose_block_move_slot_a(actor, context, sprite, stats);
                    return;
                }
            }

            switch (stats->action_flags & 0x3FFF) {
            case 8:
                if ((s16)check_actor_transition_and_start_effect(actor, context, sprite, stats) == 0) {
                    start_directional_actor_effect(actor, context, sprite, stats);
                    return;
                }
                return;

            case 9:
                clear_actor_flag_and_apply_effect(actor, context, sprite, stats);
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
                stats->facing = heading;
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
        choose_block_move_slot_a(actor, context, sprite, stats);
        return;
    } else if (!(((u32)stats->flags1C) & 0x2000)) {
        s32 room_index = (s8)room_id;

        if ((room_index < 0) || !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)stats->flags1C) & 0x430)) {

                if ((s16)test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) != 0) {
                    stats->facing = get_rounded_facing_and_rounding_flag(
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
    if (((u32)stats->flags1C) & 0x20) {
        return;
    }

    {
        u8 *main_table = glacier_direction_frames;

        if (sprite->frameTable != main_table) {
            if (sprite->frameTable != glacier_frame_set_1) {
                (sprite->frameTable) = main_table;
                select_sprite_entry(sprite,
                    main_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                    0);
                actor->unk_9E = 0;
                actor->unk_A0.parts.low = (rand() & 0x1F) + 0xF;
            }
        }

        if (sprite->frameTable == main_table) {
            s16 idle_timer = actor->unk_9E;

            actor->unk_9E = idle_timer + 1;
            if (idle_timer >= (actor->unk_A0.parts.low)) {
                ObjectNodeHeader *object;
                GlacierProjectedDepthBody *object_data;

                u8 *alt_table = glacier_frame_set_1;

                (sprite->frameTable) = alt_table;
                select_sprite_entry(sprite,
                    alt_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
                    0);
                advance_sprite_animation_and_textures(sprite);

                /* BYTES: local/global alloc priority: the loop note adds loop-weighted refs (REG_N_REFS) to a value; unwrap swaps callee-saved registers (ledger/onetrip_loadbearing.jsonl: dungeon/func_8102FCB8). */
                do {
                    object = allocate_flagged_object_node(0x212);
                } while (0);
                if (object != 0) {
                    initialize_object_rendering_and_params(object, actor, context);
                    object->update_callback = D_80170A0C;
                    object_data = NODE_BODY(object);
                    object_data->reference_position = context;
                    object_data->facing = (stats->facing);

                    {
                        SpriteFrameState *owner = ((S_801714B8_0_pre *)actor)[-1].unk_00;

                        if (resolve_record_orientation_or_fallback(
                                owner->source, owner, &spawn_offset.orientation, 0xF)) {
                            ObjectPosition *part = object->position;

                            (part->x).unsigned_parts.integer += (spawn_offset.distance[0]);
                            (part->y).unsigned_parts.integer += (spawn_offset.distance[1]);
                            (part->z).unsigned_parts.integer += (spawn_offset.distance[2]);
                        }
                    }
                    {
                        SpriteFrameState *part = object->sprite;
                        part->flags |= 0x80;
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
            state_table[((g_game_work.view.camera_rotation.parts.viewAngle + stats->facing + 0x100) >> 9) & 7],
            0);
        actor->unk_9E = 0;
        actor->unk_A0.parts.low = (rand() & 0x1F) + 0xF;
    }
}
