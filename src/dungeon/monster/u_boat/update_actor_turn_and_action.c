#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80171A80_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    union { u8 n; u8 v; } unk_9A;   /* accessed as both */
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u8 pad_A4[0xC];
    union { u8 v; u8 n; } unk_B0;   /* accessed as both */
    u8 pad_B1[0x4];
    u8 unk_B5;
} S_80171A80_0;   /* arg0 in update_actor_turn_and_action */

typedef struct S_80171A80_6 {
    u8 pad_00[0xA6];
    u16 unk_A6;
} S_80171A80_6;   /* global in update_actor_turn_and_action */

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void reset_action_and_decrement_actor_count(void *, void *, void *, void *);
void create_owner_linked_directional_object(ActorRecord *owner_data, ObjectPosition *source_position, SpriteFrameState *source_sprite);
extern void prepare_actor_directional_action(u8 *entity, ObjectPosition *action_param, SpriteFrameState *action_sprite, u8 *frame_table, s32 fallback_state);
void advance_aura_actor_turn_path(ActorRecord *actor, ObjectPosition *actor_slot, SpriteFrameState *entity_arg, ActorRecord *state_arg);
#include "dungeon/monster/u_boat.h"
extern void begin_actor_action(void *, ObjectPosition *, void *, void *);
extern s32 func_80172EA8(void *, void *, void *, s32);
extern void update_actor_action_transition(void *state, ObjectPosition *update_mode, SpriteFrameState *sprite, void *entity);
void complete_actor_action(ActorRecord *actor, ObjectPosition *unused_1, SpriteFrameState *unused_2, void *entity);
extern void begin_actor_exclusive_action(void *, ObjectPosition *, void *, s32, s32);

extern u8 uboat_default_frames[];
extern u8 uboat_ready_frames[];
extern u8 D_800E2418[];
extern u8 u_boat_frame_set[];
extern u8 uboat_action_frames[];
#include "dungeon/monster/u_boat.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"

/* Updates dungeon actor animation, status, and action dispatch. */
void update_actor_turn_and_action(void *entity, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor)
{
    u16 distance;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((S_80171A80_0 *)entity)->unk_9A.n = 0xE;
        advance_aura_actor_turn_path(entity, context, sprite, actor);
        return;
    }

    if (actor->mp_value.parts.whole == 0) {
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            void *anim_table;

            advance_actor_pending_action(entity, context, sprite, actor);
            if (sprite->frameTable == uboat_action_frames) {
                return;
            }
            anim_table = u_boat_frame_set;
            (sprite->frameTable) = anim_table;
            select_sprite_entry(sprite,
                ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            return;
        } else {
            begin_actor_exclusive_action(entity, context, sprite, 0, 0);
            return;
        }
    }

    if (((u32)actor->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == uboat_action_frames) {
            ((S_80171A80_0 *)entity)->unk_9A.n = 0xD;
            ((S_80171A80_0 *)entity)->unk_9B = 1;
            ((S_80171A80_0 *)entity)->unk_8C = 0;
            actor->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(entity, context, sprite, u_boat_frame_set) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(entity, context, sprite, actor);
            return;
        }

        if (((S_80171A80_0 *)entity)->unk_9A.v != 0xE) {
            ((S_80171A80_0 *)entity)->unk_9A.v = 0xE;
        }
        if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
            void *anim_table = uboat_default_frames;
            u8 is_active;

            if (sprite->frameTable != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                    0);
                sprite->frame_ticks = 1;
                is_active = ((S_80171A80_0 *)entity)->unk_B0.v;
                ((S_80171A80_0 *)entity)->unk_9E = 0;
                ((S_80171A80_0 *)entity)->unk_A2.s = 0;
            } else {
                is_active = ((S_80171A80_0 *)entity)->unk_B0.n;
            }
            if (is_active == 0) {
                create_owner_linked_directional_object(entity, context, sprite);
            }
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                actor->flags1C |= 0x40000;
                ((S_80171A80_0 *)entity)->unk_98 &= 0xFFF7;
            }
        }

        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(entity, context, sprite, uboat_ready_frames) != 0) {
                return;
            }
        }

        if (((u32)actor->flags1C) & ACTOR_LIFTED) {
            s16 height_delta;

            begin_actor_move_to_target_facing(entity, context, sprite, actor);
            height_delta = ((S_80171A80_0 *)entity)->unk_92.u - ((S_80171A80_0 *)entity)->unk_A2.u;
            ((S_80171A80_0 *)entity)->unk_A2.s = 0;
            ((S_80171A80_0 *)entity)->unk_9E = 0;
            ((S_80171A80_0 *)entity)->unk_92.s = height_delta;
            update_actor_action_transition(entity, context, sprite, actor);
            return;
        }

        if ((can_entity_gain_level(actor) << 16) != 0) {
            process_selected_actor_record(entity, context, sprite, actor);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x,
        sprite->tile_y);
    sprite->room_index = room_id;

    if (actor->pending_turn_updates > 0) {
        if (((u32)actor->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(actor);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            choose_and_execute_actor_step(entity, context, sprite, actor);
            return;
        }
        if (!(actor->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(actor,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((func_80172EA8(entity, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = actor->action_flags | 0x4000;
            actor->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                choose_and_execute_actor_step(entity, context, sprite, actor);
                return;
            }
        }

        action_state = actor->action_flags & ACTOR_ACTION_CODE_MASK;
        switch (action_state) {
        case 8:
            if ((try_turn_actor_toward_target(entity, context, sprite, actor) << 16) != 0) {
                return;
            }
            begin_actor_action(entity, context, sprite, actor);
            return;

        case 9:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                complete_actor_action(entity, context, sprite, actor);
                return;
            }
            begin_actor_exclusive_action(entity, context, sprite, 1, 0);
            return;

        case 10:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                reset_action_and_decrement_actor_count(entity, context, sprite, actor);
                return;
            }
            begin_actor_exclusive_action(entity, context, sprite, 1, 0);
            return;

        case 12:
            update_actor_status_and_mp(actor);
            return;

        case 5:
        case 6:
        case 7:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                ActorRecord *player;
                s16 facing;

                facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                actor->facing = facing;
                if (player->action_id.u != 0x11) {
                    update_actor_status_and_mp(actor);
                    return;
                }
                if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                    prepare_actor_directional_action(entity, context, sprite, D_800E2418, uboat_behavior_entry);
                    return;
                }
            }
            {
                S_80171A80_6 *leader = (S_80171A80_6 *)dungeon_actor_ring_anchor;

                if (leader->unk_A6 != 0) {
                    choose_and_execute_actor_step(entity, context, sprite, actor);
                    return;
                }
                leader->unk_A6 = 2;
                begin_actor_exclusive_action(entity, context, sprite, 1, 2);
                return;
            }

        case 2:
        case 1:
        case 3:
            if (((S_80171A80_0 *)entity)->unk_B5 == 0) {
                begin_actor_spell_action(entity, context, sprite, D_800E2418, uboat_behavior_entry);
                return;
            } else {
                s32 action_mode = 1;

                begin_actor_exclusive_action(entity, context, sprite,
                    1, action_mode);
                return;
            }

        case 11:
        default:
            choose_and_execute_actor_step(entity, context, sprite, actor);
            return;
        }
    }

    if (!(((u32)actor->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)actor->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    actor->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                }
            }
        }
    }
}
