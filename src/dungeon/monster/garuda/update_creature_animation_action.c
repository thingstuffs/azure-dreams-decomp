#include "engine/graphics/select_sprite_entry_api.h"
#include "dungeon/item.h"
#include "shared/object_node.h"
#include "shared/dungeon_floor.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#include "common.h"
#include "dungeon/actor/state.h"
#include "dungeon/actor/motion.h"
#include "dungeon.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"
#include "dungeon/monster/garuda.h"
#include "dungeon/player/object.h"
#include "dungeon/modules.h"
#include "dungeon/monster/hikewne.h"
#include "dungeon/monster/garuda_frames.h"

#include "dungeon/monster/dragon/transition_effect.h"
typedef void (*DungeonCallback)(void *, void *, void *, void *);
#include "dungeon/item/find_active_rect_containing_point_api.h"
extern s16 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
extern void advance_stored_entity_path(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void update_actor_action_and_direction(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80173834(void *, void *, void *, void *);
extern u8 garuda_walk_direction_frames[];
extern u8 D_80174890[];
extern u8 garuda_frame_set;
extern u8 D_801748D8[];

/* Update creature animation and dispatch its dungeon action. */
void update_creature_animation_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *creature) {
    u16 direction_aux;
    s8 room_id;
    u16 action;
    SpriteFrameState *sprite;
    u32 dungeon_flags = g_dungeon_status.flags;
    if (dungeon_flags & 0x1000) {
        actor->action_id = 0xE;
        advance_stored_entity_path(actor, context, sprite_arg, creature);
        return;
    }
    if (creature->mp_value.parts.whole == 0) {
        void *anim_table;
        advance_actor_pending_action(actor, context, sprite_arg, creature);
        if (sprite_arg->frameTable == garuda_frame_set_2) {
            return;
        }
        anim_table = D_801748D8;
        sprite_arg->frameTable = anim_table;
        select_sprite_entry(sprite_arg, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing) + 0x100) >> 9) & 7], 0);
        return;
    }
    sprite = sprite_arg;
    if ((u32)creature->flags1C & 0x200) {
        if ((sprite->frameTable) == garuda_frame_set_2) {
            actor->action_id = 0xD;
            actor->action_phase = 1;
            actor->unk_8C.word = 0;
            creature->flags1C = (u32)((u32)creature->flags1C & (0xFFFBFFFF));
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_801748D8) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if ((u32)creature->flags1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }
        {
            register void *current_anim;
            void *anim_table;
            switch (actor->action_id) {
            case 0xE:
                break;

            default:
                actor->action_id = 0xE;
                break;

            }

            current_anim = sprite->frameTable;
            anim_table = garuda_walk_direction_frames;
            if (current_anim != anim_table) {
                sprite->frameTable = anim_table;
                select_sprite_entry(sprite, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing) + 0x100) >> 9) & 7], 0);
                sprite->frame_ticks = 1;
                actor->unk_A4.halves.high.s = 0;
                actor->unk_B0.halves.high.s = 0;
            }
        }
        creature->flags1C = (u32)((u32)creature->flags1C | (0x40000));
        actor->action_state_flags &= 0xFFF7;
        if (creature->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174890) != 0) {
                return;
            }
        }
        if ((u32)creature->flags1C & 0x80000) {
            s16 adjusted_offset;
            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            adjusted_offset = actor->unk_90.parts.high - actor->unk_A4.halves.high.u;
            actor->unk_A4.halves.high.s = 0;
            actor->unk_B0.halves.high.s = 0;
            actor->unk_90.parts.high = adjusted_offset;
            func_80173834(actor, context, sprite, creature);
            return;
        }
        if ((can_entity_gain_level(creature) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }
    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;
    if (creature->pending_turn_updates > 0) {
        if ((u32)creature->flags1C & 0x20) {
            update_actor_status_and_mp(creature);
            return;
        }
        if ((*(u16 *)&sprite->tile_x) == (reference_tile_object.tile_position.word)) {
            choose_block_move_slot_a(actor, context, sprite, creature);
            return;
        }
        if (!(creature->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = NODE_BODY(previous_node);
                    previous_actor = previous_body;
                    if ((check_entity_relation(creature, previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((update_entity_state_from_query(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = creature->action_flags | 0x4000;
            creature->action_flags = action;
            if (!(action & 0x8000)) {
                choose_block_move_slot_a(actor, context, sprite, creature);
                return;
            }
        }
        action = creature->action_flags & 0x3FFF;
        if (((u32) (action - 1)) >= 12) {
            choose_block_move_slot_a(actor, context, sprite, creature);
            return;
        }
        switch (action - 1) {
        case 8:
        {
            void *target = probe_directional_neighbor(creature, sprite->tile_x, sprite->tile_y, creature->facing);
            *((void **) (((u8 *) actor) + 0xA8)) = target;
            if (target == 0) {
                choose_block_move_slot_a(actor, context, sprite, creature);
                return;
            }
            if (check_global_or_linked_flag_20000(target) != 0) {
                choose_block_move_slot_a(actor, context, sprite, creature);
                return;
            }
            if ((*((((u8 *) (*((void **) (((u8 *) actor) + 0xA8)))) + 0x13))) < 0x33) {
                advance_actor_walk_animation(actor, context, sprite, creature);
                return;
            }
            choose_block_move_slot_a(actor, context, sprite, creature);
            return;
        }
        case 7:
            if ((check_actor_transition_and_start_effect(actor, context, sprite, creature) << 16) != 0) {
                return;
            }
            update_actor_action_and_direction(actor, context, sprite, creature);
            return;
        case 4:
        case 5:
        case 6:
        {
            TileObject *player_pos = &reference_tile_object;
            ActorRecord *player;
            s16 facing_angle;
            facing_angle = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y, &direction_aux);
            player = primary_actor_record;
            creature->facing = facing_angle;
            if (player->action_id == 0x11) {
                begin_actor_spell_action(actor, context, sprite, &garuda_frame_set, update_creature_animation_action);
                return;
            }
        }
        case 11:
            update_actor_status_and_mp(creature);
            return;
        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, &garuda_frame_set, update_creature_animation_action);
            return;
        case 3:
        case 9:
        case 10:
        default:
            choose_block_move_slot_a(actor, context, sprite, creature);
            return;
        }
    }
    if (!((u32)creature->flags1C & 0x2000)) {
        s32 room_index = room_id;
        if ((room_index < 0) || (!(dungeon_rooms[room_index].flags & 2))) {
            if (!((u32)creature->flags1C & 0x430)) {
                TileObject *player_pos = &reference_tile_object;
                if ((test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
                    player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x,
                        sprite->tile_y, player_pos->tile_position.parts.tile_x,
                        player_pos->tile_position.parts.tile_y, &direction_aux);
                }
            }
        }
    }
    return;

}
