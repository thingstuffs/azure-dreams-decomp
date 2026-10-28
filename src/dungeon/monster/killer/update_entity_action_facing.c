#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s32 find_active_rect_containing_point(s32, s32);
extern s32 test_neighbor_position_relation(s32, s32, s32, s32);
extern s32 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);
extern void func_80171438(ActorRecord *action, ObjectPosition *action_id, SpriteFrameState *entity, ActorRecord *move_state);
extern void func_8017167C(void *, void *, void *, void *);
extern s32 validate_direction_and_initialize_action(void *, ObjectPosition *, void *, void *);
void update_eligible_actor_action_alt(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 func_80172230(void *, void *, void *, s32);
extern void func_80173A84(void *, void *, void *, void *);

extern u8 killer_action_resume_address;
#include "dungeon/monster/killer.h"
extern u8 D_80174040[];
extern u8 D_80174070[];
extern u8 killer_frame_set[];
extern u8 killer_frame_set_2[];

typedef struct S_80170EA8_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    union { u16 n; u16 v; } unk_98;   /* accessed as both */
    u8 unk_9A;
    u8 unk_9B;
} S_80170EA8_0;   /* arg0 in update_entity_action_facing */

/* Updates the entity action, facing direction, and animation from dungeon state. */
/* Selects Killer's movement, two attack modes, spells, and turn processing, then restores its directional
 * idle frames. */
void update_entity_action_facing(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    u8 *anim_table;
    s32 tile_record;
    u16 direction_aux;
    u32 dungeon_flags = g_dungeon_status.flags;

    if (dungeon_flags & 0x1000) {
        actor->action_id.u = 0xE;
        func_80171438(actor, context, sprite, entity);
        return;
    }

    if (entity->mp_value.parts.whole == 0) {
        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->frameTable != killer_frame_set_2) {
            (sprite->frameTable) = killer_frame_set;
            select_sprite_entry(sprite,
                killer_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == killer_frame_set_2) {
            actor->action_id.u = 0xD;
            actor->action_phase.u = 1;
            ((S_80170EA8_0 *)actor)->unk_8C = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, killer_frame_set)) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        if (actor->action_id.u != 0xE) {
            u8 next_state = 0xE;

            anim_table = killer_direction_frames;
            if (sprite->frameTable != anim_table) {
                (sprite->frameTable) = anim_table;
                select_sprite_entry(sprite,
                    anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                    0);
            }
            actor->action_id.u = next_state;
        }

        actor->action_state_flags &= 0xFFF3;
        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174040)) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_80173A84(actor, context, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    tile_record = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = tile_record;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            func_8017167C(actor, context, sprite, entity);
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
                    if ((s16)check_entity_relation(entity,
                            previous_actor) != 0) {
                        return;
                    }
                }
            }
            if ((s16)func_80172230(actor, context, sprite, 0) == 0) {
                return;
            }
            entity->action_flags |= 0x4000;
            if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
                func_8017167C(actor, context, sprite, entity);
            return;
            }
        }

        switch (entity->action_flags & ACTOR_ACTION_CODE_MASK) {
        case 9:
            actor->action_state_flags |= 0x8000;
            /* fallthrough */
        case 8:
            if (((u32)entity->flags1C) & ACTOR_PLAYER_SIDE) {
                if ((entity->action_flags & ACTOR_ACTION_CODE_MASK) == 8) {
                    actor->action_state_flags &= 0x7FFF;
                }
            }
            if ((s16)validate_direction_and_initialize_action(actor, context, sprite, entity) == 0) {
                update_eligible_actor_action_alt(actor, context, sprite, entity);
                return;
            }
            return;
        case 5:
        case 6:
        case 7:
            {
                ActorRecord *global_actor;
                s32 direction;

                direction = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_aux);
                global_actor = primary_actor_record;
                entity->facing = direction;
                if (global_actor->action_id.u == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_80174070, &killer_action_resume_address);
                    return;
                }
            }
            /* fallthrough */
        case 12:
            update_actor_status_and_mp(entity);
            return;
        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(actor, context, sprite, D_80174070, &killer_action_resume_address);
            return;
        default:
            func_8017167C(actor, context, sprite, entity);
            return;
        }
    } else if (!(((u32)entity->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 record_index = (s8)tile_record;

        if ((record_index < 0) || !(dungeon_rooms[record_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((s16)test_neighbor_position_relation(sprite->tile_x,
                        sprite->tile_y, reference_tile_object.tile_position.parts.tile_x,
                        reference_tile_object.tile_position.parts.tile_y) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_aux);
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
    anim_table = killer_direction_frames;
    if (sprite->frameTable == anim_table) {
        return;
    }
    (sprite->frameTable) = anim_table;
    select_sprite_entry(sprite,
        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + (u32)anim_table),
        0);
}
