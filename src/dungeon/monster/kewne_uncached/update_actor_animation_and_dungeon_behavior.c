#include "engine/graphics/select_sprite_entry_api.h"
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
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/monster/kewne_uncached.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon/monster/kewne.h"
#include "dungeon/monster/kewne_uncached_frames.h"


extern s8 find_active_rect_containing_point(s32, s32);
extern void select_bank_actor_movement(ActorRecord *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
extern s32 select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *visual_data, ActorRecord *actor);
extern void func_8015D078(void *, void *, void *, void *);

extern u8 D_80159FA4[];
extern u8 D_8015DC38[];
extern u8 D_8015DC88[];
extern u8 D_8015DC90[];
extern u8 D_8015DCA0[];
extern u8 D_8015DCA8[];

/* Updates an actor's animation and dispatches its dungeon behavior. */
void update_actor_animation_and_dungeon_behavior(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 distance;
    s8 room_id;
    u16 behavior;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id = 0xE;
        advance_actor_path_and_facing(actor, context, sprite, entity);
        return;
    }
    if (entity->mp_value.parts.whole == 0) {
        void *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->frameTable == D_8015DC90) {
            return;
        }
        anim_table = D_8015DCA0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_8015DC90) {
            actor->action_id = 0xD;
            actor->action_phase = 1;
            actor->unk_8C.word = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_8015DCA0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }

        {
            u8 current_state = actor->action_id;
            u32 next_state = 0xE;
            void *current_anim;

            if (current_state != next_state) {
                actor->action_id = next_state;
                actor->unk_B4.halves.high.s = 0;
            }
            current_anim = sprite->frameTable;
            if (current_anim == D_8015DCA8) {
                if (sprite->flags & 0xE000) {
                    (sprite->frameTable) = kewne_uncached_frame_set_2;
                    select_sprite_entry(sprite,
                        kewne_uncached_frame_set_2[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.parts.high = 0;
                    actor->unk_9E = 0;
                }
            } else {
                void *idle_anim = kewne_uncached_frame_set_2;
                if (current_anim != idle_anim) {
                    (sprite->frameTable) = idle_anim;
                    select_sprite_entry(sprite,
                        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7) + (u32)idle_anim),
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.parts.high = 0;
                    actor->unk_9E = 0;
                }
            }
        }

        entity->flags1C = (u32)((u32)(entity->flags1C) | (0x40000));
        actor->action_state_flags &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_8015DC38) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            s16 movement_delta;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            movement_delta = actor->unk_90.parts.high - actor->unk_A0.parts.high;
            actor->unk_A0.parts.high = 0;
            actor->unk_9E = 0;
            actor->unk_90.parts.high = movement_delta;
            func_8015D078(actor, context, sprite, entity);
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
        if ( *(u16 *)&sprite->tile_x !=reference_tile_object.tile_position.word) {
            if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
                if (g_dungeon_status.flags & 0x2000) {
                    {
                        ObjectNodeHeader *previous_node;
                        void *previous_body;
                        ActorRecord *previous_actor;

                        previous_node = primary_actor_record->previous_actor_header;
                        previous_body = NODE_BODY(previous_node);
                        previous_actor = previous_body;
                        if ((check_entity_relation(entity,
                                previous_actor) << 16) != 0) {
                            return;
                        }
                    }
                }
                if ((update_entity_state_from_query(actor, context, sprite, 0) << 16) == 0) {
                    return;
                }
                behavior = entity->action_flags | 0x4000;
                entity->action_flags = behavior;
            }

            if (entity->action_flags & ACTOR_ACTION_PENDING) {
                behavior = entity->action_flags & ACTOR_ACTION_CODE_MASK;
                switch (behavior) {
                case 8:
                case 9:
                    if ((select_and_start_target_action(actor, context, sprite, entity) << 16) != 0) {
                        return;
                    }
                    start_kewne_attack_action(actor, context, sprite, entity);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    ActorRecord *player;
                    s16 facing_angle;

                    facing_angle = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                    player = primary_actor_record;
                    entity->facing = facing_angle;
                    if (player->action_id == 0x11) {
                        begin_actor_spell_action(actor, context, sprite, D_8015DC88, D_80159FA4);
                        return;
                    }
                }

                case 12:
                    update_actor_status_and_mp(entity);
                    return;

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(actor, context, sprite, D_8015DC88, D_80159FA4);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }

        select_bank_actor_movement(actor, context, sprite, entity);
        return;
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
                }
            }
        }
    }
}
