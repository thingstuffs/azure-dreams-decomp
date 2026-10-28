#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/monster/kewne.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/entity.h"

typedef struct S_801710EC_0 {
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
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_801710EC_0;   /* arg0 in update_actor_animation_and_behavior */

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);

extern void func_80171854(ActorRecord *move_data, ObjectPosition *context, SpriteFrameState *position_data, ActorRecord *actor_data);
s32 select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *visual_data, ActorRecord *actor);
extern void clear_actor_flag_and_update_action(ActorRecord *controller, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
extern void advance_counter_unblocked_and_reset_action(void *, void *, void *, void *);
extern void update_actor_state_after_map_check(void *, ObjectPosition *, void *, ActorRecord *);

extern u8 kewne_direction_frames[];
extern u8 D_80175E48[];
extern u8 D_80175E98[];
extern u8 kewne_frame_set_1[];
extern u8 D_80175EB0[];
extern u8 kewne_turn_frames[];

/* Updates actor animation and dispatches dungeon behavior based on status and position. */
/* Selects Kewne's movement, attacks, spells, and turn processing while resetting its idle animation and
 * vertical offsets. */
void update_actor_animation_and_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 distance;
    s8 room_id;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id.u = 0xE;
        advance_actor_path_and_facing(actor, context, sprite, entity);
        return;
    }

    if (entity->mp_value.parts.whole == 0) {
        u8 *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->frameTable == kewne_frame_set_1) {
            return;
        }
        anim_table = D_80175EB0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == kewne_frame_set_1) {
            actor->action_id.u = 0xD;
            actor->action_phase.u = 1;
            ((S_801710EC_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_80175EB0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        {
            void *current_anim;
            u8 *anim_table;

            if (actor->action_id.u != 0xE) {
                actor->action_id.u = 0xE;
                ((S_801710EC_0 *)actor)->unk_B2 = 0;
            }

            current_anim = sprite->frameTable;
            if (current_anim == kewne_turn_frames) {
                if (sprite->flags & 0xE000) {
                    u8 *reset_anim = kewne_direction_frames;

                    (sprite->frameTable) = reset_anim;
                    select_sprite_entry(sprite,
                        reset_anim[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.parts.high = 0;
                    actor->unk_9E.s = 0;
                }
            } else {
                anim_table = kewne_direction_frames;
                if (current_anim != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.parts.high = 0;
                    actor->unk_9E.s = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        actor->action_state_flags &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80175E48) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            adjusted_offset = actor->unk_90.parts.high.u - actor->unk_A0.parts.high;
            actor->unk_A0.parts.high = 0;
            actor->unk_9E.s = 0;
            actor->unk_90.parts.high.s = adjusted_offset;
            update_actor_state_after_map_check(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_80171854(actor, context, sprite, entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(entity,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((resolve_monster_move_choice(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = entity->action_flags | 0x4000;
            entity->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                func_80171854(actor, context, sprite, entity);
            return;
            }
        }

        {
            u32 action_index = (u32)((entity->action_flags & ACTOR_ACTION_CODE_MASK) - 1);

            switch (action_index) {
            case 7:
            case 8:
                if ((select_and_start_target_action(actor, context, sprite, entity) << 16) != 0) {
                    return;
                }
                clear_actor_flag_and_update_action(actor, context, sprite, entity);
                return;

            case 4:
            case 5:
            case 6:
            {
                ActorRecord *player;
                s16 facing_angle;

                facing_angle = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                entity->facing = facing_angle;
                if (player->action_id.u == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80175E98, update_actor_animation_and_behavior);
                    return;
                }
            }
                                            /* fallthrough */

            case 11:
                update_actor_status_and_mp(entity);
                return;

            case 0:
            case 1:
            case 2:
                begin_actor_spell_action(actor, context, sprite, D_80175E98, update_actor_animation_and_behavior);
                return;

            case 3:
            case 9:
            case 10:
            default:
                func_80171854(actor, context, sprite, entity);
                return;
            }
        }
    }

    if (!(((u32)entity->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                    return;
                }
            }
        }
    } else if ((get_entity_effect_value(entity, STATUS_PARALYSIS) << 16) == 0) {
        if (primary_actor_record->action_id.u == 0x17) {
            advance_counter_unblocked_and_reset_action(actor, context, sprite, entity);
        }
    }
}
