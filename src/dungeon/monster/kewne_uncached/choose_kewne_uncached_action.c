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


extern void select_sprite_entry(void *, s32, s32);
extern s8 find_active_rect_containing_point(s32, s32);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void select_bank_actor_movement(ActorRecord *, ObjectPosition *, SpriteFrameState *, ActorRecord *);
extern s32 select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *visual_data, ActorRecord *actor);
extern void func_8016F078(void *, void *, void *, void *);

extern u8 D_8016BFA4[];
extern u8 D_8016FC30[];
extern u8 D_8016FC38[];
extern u8 D_8016FC88[];
extern u8 D_8016FC90[];
extern u8 D_8016FCA0[];
extern u8 D_8016FCA8[];

/* Updates actor animation, facing, and action handling from dungeon state. */
void choose_kewne_uncached_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 direction_flags;
    s8 area_id;
    u16 action;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id = 0xE;
        advance_actor_path_and_facing(actor, context, sprite, entity);
        return;
    }
    if (entity->mp_value.parts.whole == 0) {
        void *anim_table;

        advance_actor_pending_action(actor, context, sprite, entity);
        if (sprite->frameTable == D_8016FC90) {
            return;
        }
        anim_table = D_8016FCA0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_8016FC90) {
            actor->action_id = 0xD;
            actor->action_phase = 1;
            actor->unk_8C.word = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_8016FCA0) != 0) {
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
            void *anim_table;

            if (current_state != next_state) {
                actor->action_id = next_state;
                actor->unk_B4.halves.high.s = 0;
            }
            current_anim = sprite->frameTable;
            if (current_anim == D_8016FCA8) {
                if (sprite->flags & 0xE000) {
                    void *idle_anim; /* MATCH: form the jump arm anim_table address in a1. */
                    idle_anim = D_8016FC30;
                    (sprite->frameTable) = idle_anim;
                    select_sprite_entry(sprite,
                        ((u8 *)idle_anim)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.halves.high.s = 0;
                    actor->unk_9E = 0;
                }
            } else {
                anim_table = D_8016FC30;
                if (current_anim != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.halves.high.s = 0;
                    actor->unk_9E = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        actor->action_state_flags &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_8016FC38) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            s16 base_height;

            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            base_height = actor->unk_90.parts.high.u - actor->unk_A0.parts.high;
            actor->unk_A0.halves.high.s = 0;
            actor->unk_9E = 0;
            actor->unk_90.parts.high.s = base_height;
            func_8016F078(actor, context, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, entity);
        }
    }

    area_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = area_id;

    if (entity->pending_turn_updates > 0) {
        if (((u32)entity->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            select_bank_actor_movement(actor, context, sprite, entity);
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
            if ((update_entity_state_from_query(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = entity->action_flags | 0x4000;
            entity->action_flags = action;
        }

        if (entity->action_flags & ACTOR_ACTION_PENDING) {
            action = entity->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (action) {
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
                s16 facing;

                facing = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &direction_flags);
                player = primary_actor_record;
                entity->facing = facing;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_8016FC88, D_8016BFA4);
                    return;
                }
            }

            case 12:
                update_actor_status_and_mp(entity);
                return;

            case 1:
            case 2:
            case 3:
                begin_actor_spell_action(actor, context, sprite, D_8016FC88, D_8016BFA4);
                return;

            case 11:
            default:
                break;
            }
        }
        select_bank_actor_movement(actor, context, sprite, entity);
        return;
    }

    if (!(((u32)entity->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 area_index = area_id;

        if ((area_index < 0) ||
            !(dungeon_rooms[area_index].flags & 2)) {
            if (!(((u32)entity->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &direction_flags);
                }
            }
        }
    }
}
