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
#include "dungeon/player/object.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon/monster/kewne.h"

extern void select_sprite_entry(void *, s32, s32);
extern s8 find_active_rect_containing_point(s32, s32);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void select_bank_actor_movement(void *, void *, void *, void *);
extern s32 select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *visual_data, ActorRecord *actor);
extern void func_80175078(void *, void *, void *, void *);

extern u8 kewne_uncached_action_resume_address[];
extern u8 kewne_uncached_frame_set_1[];
extern u8 D_80175C38[];
extern u8 D_80175C88[];
extern u8 D_80175C90[];
extern u8 D_80175CA0[];
extern u8 D_80175CA8[];


/* Update dungeon actor animation, behavior, and facing. */
void update_actor_animation_behavior_and_facing(void *actor, ObjectPosition *actor_aux, SpriteFrameState *sprite, ActorRecord *entity) {
    u16 distance;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((ActorRecord *)actor)->action_id.u = 0xE;
        advance_actor_path_and_facing(actor, actor_aux, sprite, entity);
        return;
    }
    if (entity->mp_value.parts.whole == 0) {
        void *anim_table;

        advance_actor_pending_action(actor, actor_aux, sprite, entity);
        if (sprite->frameTable == D_80175C90) {
            return;
        }
        anim_table = D_80175CA0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)entity->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_80175C90) {
            ((ActorRecord *)actor)->action_id.u = 0xD;
            ((ActorRecord *)actor)->action_phase.u = 1;
            ((ActorRecord *)actor)->unk_8C.word = 0;
            entity->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, actor_aux, sprite, D_80175CA0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)entity->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, actor_aux, sprite, entity);
            return;
        }

        {
            u8 current_state = ((ActorRecord *)actor)->action_id.u;
            u32 idle_state = 0xE;
            void *current_anim;
            void *anim_table;

            if (current_state != idle_state) {
                ((ActorRecord *)actor)->action_id.u = idle_state;
                ((ActorRecord *)actor)->unk_B4.halves.high.s = 0;
            }
            current_anim = sprite->frameTable;
            if (current_anim == D_80175CA8) {
                if (sprite->flags & 0xE000) {
                    register void *idle_anim; /* MATCH: the first arm materializes the animation anim_table in a1. */
                    idle_anim = kewne_uncached_frame_set_1;
                    (sprite->frameTable) = idle_anim;
                    select_sprite_entry(sprite,
                        ((u8 *)idle_anim)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    ((ActorRecord *)actor)->unk_A0.halves.high.s = 0;
                    ((ActorRecord *)actor)->unk_9E.s = 0;
                }
            } else {
                anim_table = kewne_uncached_frame_set_1;
                if (current_anim != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    ((ActorRecord *)actor)->unk_A0.halves.high.s = 0;
                    ((ActorRecord *)actor)->unk_9E.s = 0;
                }
            }
        }

        entity->flags1C |= 0x40000;
        ((ActorRecord *)actor)->action_state_flags &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, actor_aux, sprite, D_80175C38) != 0) {
                return;
            }
        }

        if (((u32)entity->flags1C) & ACTOR_LIFTED) {
            s16 adjusted_angle;

            begin_actor_move_to_target_facing(actor, actor_aux, sprite, entity);
            adjusted_angle = ((ActorRecord *)actor)->unk_90.parts.high.u - ((ActorRecord *)actor)->unk_A0.parts.high;
            ((ActorRecord *)actor)->unk_A0.halves.high.s = 0;
            ((ActorRecord *)actor)->unk_9E.s = 0;
            ((ActorRecord *)actor)->unk_90.parts.high.s = adjusted_angle;
            func_80175078(actor, actor_aux, sprite, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            process_selected_actor_record(actor, actor_aux, sprite, entity);
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
            select_bank_actor_movement(actor, actor_aux, sprite, entity);
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
            if ((update_entity_state_from_query(actor, actor_aux, sprite, 0) << 16) == 0) {
                return;
            }
            action_state = entity->action_flags | 0x4000;
            entity->action_flags = action_state;
        }

        if (entity->action_flags & ACTOR_ACTION_PENDING) {
            action_state = entity->action_flags & ACTOR_ACTION_CODE_MASK;
            switch (action_state - 1) {
            case 7:
            case 8:
                if ((select_and_start_target_action(actor, actor_aux, sprite, entity) << 16) != 0) {
                    return;
                }
                start_kewne_attack_action(actor, actor_aux, sprite, entity);
                return;

            case 4:
            case 5:
            case 6:
            {
                ActorRecord *player;
                s16 heading;

                heading = get_rounded_facing_and_rounding_flag(
                    sprite->tile_x, sprite->tile_y,
                    reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                    &distance);
                player = primary_actor_record;
                entity->facing = heading;
                if (player->action_id.u == 0x11) {
                    begin_actor_spell_action(actor, actor_aux, sprite, D_80175C88, kewne_uncached_action_resume_address);
                    return;
                }
            }

            case 11:
                update_actor_status_and_mp(entity);
                return;

            case 0:
            case 1:
            case 2:
                begin_actor_spell_action(actor, actor_aux, sprite, D_80175C88, kewne_uncached_action_resume_address);
                return;

            case 3:
            case 9:
            case 10:
            default:
                break;
            }
        }
        select_bank_actor_movement(actor, actor_aux, sprite, entity);
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
