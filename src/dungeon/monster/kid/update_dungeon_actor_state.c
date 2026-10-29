#include "shared/object_node.h"
#include "common.h"
#include "dungeon/monster/kid.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

typedef struct S_80171400_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171400_1;   /* arg3 in update_dungeon_actor_state */

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
extern void func_80171B28(void *, void *, void *, void *);
extern s32 func_80172270(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor);
void initialize_status_gated_action(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *animation, ActorRecord *entity);
extern s16 func_80172554(void *, void *, void *, s32);
extern void func_80174218(void *, void *, void *, void *);

extern u8 kid_direction_frames[];
extern u8 kid_alt_direction_frames[];
extern u8 D_80175150[];
extern u8 kid_frame_set_1[];
extern u8 kid_frame_set_2[];
extern u8 kid_frame_set_3[];
extern u8 kid_alt_spawn_direction_frames[];
extern u8 kid_frame_set_4[];

/* Updates a dungeon actor's state, animation, and facing direction. */
void update_dungeon_actor_state(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_in, ActorRecord *entity) {
    u16 direction_aux;
    s8 room_id;
    u16 action_state;
    u32 dungeon_flags = g_dungeon_status.flags;

    if (dungeon_flags & 0x1000) {
        actor->action_id.u = 0xE;
        advance_stored_actor_path(actor, context, sprite_in, entity);
        return;
    }

    if (entity->mp_value.parts.whole == 0) {
        u8 *anim_table;

        advance_actor_pending_action(actor, context, sprite_in, entity);
        if (sprite_in->frameTable == kid_alt_spawn_direction_frames) {
            return;
        }
        anim_table = kid_frame_set_3;
        (sprite_in->frameTable) = anim_table;
        select_sprite_entry(sprite_in,
            anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80171400_1 *)entity)->unk_1C & 0x200) {
        if (sprite_in->frameTable == kid_frame_set_4) {
            actor->action_id.u = 0xD;
            actor->action_phase.u = 1;
            ((Rec_func_800A9E70_arg0 *)actor)->unk_8C = 0;
            ((S_80171400_1 *)entity)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite_in, kid_frame_set_3) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80171400_1 *)entity)->unk_1C & 0x100) {
            begin_pushed_actor_move(actor, context, sprite_in, entity);
            return;
        }

        if (actor->action_id.u != 0xE) {
            actor->action_id.u = 0xE;
        }

        if ((sprite_in->frameTable != kid_direction_frames) &&
            (sprite_in->frameTable != kid_alt_direction_frames)) {
            u8 *anim_table = kid_direction_frames;

            actor->unk_A8.s = 0;
            (sprite_in->frameTable) = anim_table;
            select_sprite_entry(sprite_in,
                anim_table[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                actor->unk_A8.s);
        }

        ((S_80171400_1 *)entity)->unk_1C |= 0x40000;
        actor->action_state_flags &= 0xFFF7;

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite_in, D_80175150) != 0) {
                return;
            }
        }

        if (((S_80171400_1 *)entity)->unk_1C & 0x80000) {
            begin_actor_move_to_target_facing(actor, context, sprite_in, entity);
            actor->unk_A8.s = 0;
            func_80174218(actor, context, sprite_in, entity);
            return;
        }

        if ((can_entity_gain_level(entity) << 16) != 0) {
            if ((process_selected_actor_record(actor, context, sprite_in, entity) << 16) != 0) {
                initialize_counted_entity_action(actor, context, sprite_in, entity);
            }
        }
    }

    room_id = find_active_rect_containing_point(sprite_in->tile_x, sprite_in->tile_y);
    sprite_in->room_index = room_id;

    if (entity->pending_turn_updates > 0) {
        if (((S_80171400_1 *)entity)->unk_1C & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite_in->tile_x == reference_tile_object.tile_position.word) {
            func_80171B28(actor, context, sprite_in, entity);
            return;
        }
        if (!(entity->action_flags & 0x8000)) {
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
            if ((func_80172554(actor, context, sprite_in, 0) << 16) == 0) {
                return;
            }
            action_state = entity->action_flags | 0x4000;
            entity->action_flags = action_state;
            if (!(action_state & 0x8000)) {
                func_80171B28(actor, context, sprite_in, entity);
                return;
            }
        }

        switch ((entity->action_flags & 0x3FFF) - 1) {
        case 7:
        case 8:
            if ((func_80172270(actor, context, sprite_in, entity) << 16) != 0) {
                return;
            }
            initialize_status_gated_action(actor, context, sprite_in, entity);
            return;

        case 11:
            update_actor_status_and_mp(entity);
            return;

        case 4:
        case 5:
        case 6:
        {
            ActorRecord *player;
            s16 direction;

            direction = get_rounded_facing_and_rounding_flag(
                sprite_in->tile_x, sprite_in->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
            player = primary_actor_record;
            entity->facing = direction;
            if (player->action_id.u != 0x11) {
                update_actor_status_and_mp(entity);
                return;
            }
        }

        case 0:
        case 1:
        case 2:
        {
            void *anim_table;

            if (sprite_in->frameTable == kid_direction_frames) {
                anim_table = kid_frame_set_1;
            } else {
                anim_table = kid_frame_set_2;
            }
            begin_actor_spell_action(actor, context, sprite_in, anim_table, update_dungeon_actor_state);
            return;
        }

        default:
            func_80171B28(actor, context, sprite_in, entity);
            return;
        }
    }

    if (!(((S_80171400_1 *)entity)->unk_1C & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) || !(dungeon_rooms[room_index].flags & 2)) {
            if (!(((S_80171400_1 *)entity)->unk_1C & 0x430)) {

                if ((test_neighbor_position_relation(
                        sprite_in->tile_x, sprite_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                    entity->facing = get_rounded_facing_and_rounding_flag(
                        sprite_in->tile_x, sprite_in->tile_y,
                        reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y, &direction_aux);
                }
            }
        }
    }
}
