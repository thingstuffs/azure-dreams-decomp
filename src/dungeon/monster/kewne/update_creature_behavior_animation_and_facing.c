#include "engine/graphics/select_sprite_entry_api.h"
#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "engine/entity.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "dungeon/actor/state.h"
#include "dungeon.h"
#include "dungeon/level.h"
#include "dungeon/monster/kewne.h"
#include "dungeon/player/object.h"
#include "dungeon/monster/hikewne.h"


extern s8 find_active_rect_containing_point(s32, s32);
extern s32 select_and_start_target_action(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *visual_data, ActorRecord *actor);
extern void update_kewne_charge_counter(void *, void *, void *, void *);
extern void func_8016E574(void *, void *, void *, void *);

extern u8 D_8016FE40[];
extern u8 D_8016FE48[];
extern u8 D_8016FE98[];
extern u8 D_8016FEA0[];
extern u8 D_8016FEB0[];
extern u8 D_8016FEB8[];

/* Updates creature behavior, animation, and facing according to its current state. */
void update_creature_behavior_animation_and_facing(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *creature) {
    u16 distance;
    s8 room_id;
    u16 action_flags;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id = 0xE;
        advance_actor_path_and_facing(actor, context, sprite, creature);
        return;
    }

    if (creature->mp_value.parts.whole == 0) {
        u8 *anim_table;

        advance_actor_pending_action(actor, context, sprite, creature);
        if (sprite->frameTable == D_8016FEA0) {
            return;
        }
        anim_table = D_8016FEB0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_8016FEA0) {
            actor->action_id = 0xD;
            actor->action_phase = 1;
            actor->unk_8C.word = 0;
            creature->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_8016FEB0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }

        {
            void *current_anims;
            u8 *anim_table;

            if (actor->action_id != 0xE) {
                actor->action_id = 0xE;
                actor->unk_B0.halves.high.s = 0;
            }

            current_anims = sprite->frameTable;
            if (current_anims == D_8016FEB8) {
                if (sprite->flags & 0xE000) {
                    u8 *reset_anims = D_8016FE40;

                    (sprite->frameTable) = reset_anims;
                    select_sprite_entry(sprite,
                        reset_anims[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.parts.high = 0;
                    actor->unk_9E = 0;
                }
            } else {
                anim_table = D_8016FE40;
                if (current_anims != anim_table) {
                    (sprite->frameTable) = anim_table;
                    select_sprite_entry(sprite,
                        anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    actor->unk_A0.parts.high = 0;
                    actor->unk_9E = 0;
                }
            }
        }

        creature->flags1C |= 0x40000;
        actor->action_state_flags &= 0xFFF7;

        if (creature->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_8016FE48) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & ACTOR_LIFTED) {
            s16 base_offset;

            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            base_offset = actor->unk_90.parts.high - actor->unk_A0.parts.high;
            actor->unk_A0.parts.high = 0;
            actor->unk_9E = 0;
            actor->unk_90.parts.high = base_offset;
            func_8016E574(actor, context, sprite, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (creature->pending_turn_updates > 0) {
        if (((u32)creature->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(creature);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            select_movement_direction_and_advance(actor, context, sprite, creature);
            return;
        }
        if (!(creature->action_flags & ACTOR_ACTION_PENDING)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(creature,
                            previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((update_entity_state_from_query(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action_flags = creature->action_flags | 0x4000;
            creature->action_flags = action_flags;
            if (!(action_flags & 0x8000)) {
                select_movement_direction_and_advance(actor, context, sprite, creature);
                return;
            }
        }

        {
            u32 action_index = (u32)((creature->action_flags & ACTOR_ACTION_CODE_MASK) - 1);

            switch (action_index) {
            case 7:
            case 8:
                if ((select_and_start_target_action(actor, context, sprite, creature) << 16) != 0) {
                    return;
                }
                start_kewne_attack_action(actor, context, sprite, creature);
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
                creature->facing = facing_angle;
                if (player->action_id == 0x11) {
                    begin_actor_spell_action(actor, context, sprite, D_8016FE98, update_creature_behavior_animation_and_facing);
                    return;
                }
            }
                                            /* fallthrough */

            case 11:
                update_actor_status_and_mp(creature);
                return;

            case 0:
            case 1:
            case 2:
                begin_actor_spell_action(actor, context, sprite, D_8016FE98, update_creature_behavior_animation_and_facing);
                return;

            case 3:
            case 9:
            case 10:
            default:
                select_movement_direction_and_advance(actor, context, sprite, creature);
                return;
            }
        }
    }

    if (!(((u32)creature->flags1C) & ACTOR_PLAYER_SIDE)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & (ACTOR_BLIND | ACTOR_PARALYZED | ACTOR_CONFUSED))) {

                if ((test_neighbor_position_relation(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = get_rounded_facing_and_rounding_flag(
                        sprite->tile_x, sprite->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                        &distance);
                    return;
                }
            }
        }
    } else if ((get_entity_effect_value(creature, STATUS_PARALYSIS) << 16) == 0) {
        if (primary_actor_record->action_id == 0x17) {
            update_kewne_charge_counter(actor, context, sprite, creature);
        }
    }
}
