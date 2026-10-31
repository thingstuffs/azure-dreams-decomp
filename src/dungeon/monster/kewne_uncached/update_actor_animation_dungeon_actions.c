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

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80154510(void *motion, ObjectPosition *unused, SpriteFrameState *actor, void *path_state);
extern void func_801546C8(void *, void *, void *, void *);
extern s32 func_80154E10(ActorRecord *action_state, ObjectPosition *action_param, SpriteFrameState *visual_data, ActorRecord *actor);
extern void func_801550A8(ActorRecord *controller, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 func_801551CC(void *, void *, void *, void *);
extern void func_80157078(void *, void *, void *, void *);

extern u8 D_80153FA4[];
extern u8 kewne_uncached_frame_set[];
extern u8 D_80157C38[];
extern u8 D_80157C88[];
extern u8 D_80157C90[];
extern u8 D_80157CA0[];
extern u8 D_80157CA8[];

/* Updates the actor animation and dispatches dungeon actions based on its state. */
void update_actor_animation_dungeon_actions(ActorRecord *body, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor) {
    u16 distance;
    s8 room_id;
    u16 action;

    if (g_dungeon_status.flags & 0x1000) {
        body->action_id.u = 0xE;
        func_80154510(body, context, sprite, actor);
        return;
    }
    if (actor->mp_value.parts.whole == 0) {
        void *anim_table;

        advance_actor_pending_action(body, context, sprite, actor);
        if (sprite->frameTable == D_80157C90) {
            return;
        }
        anim_table = D_80157CA0;
        (sprite->frameTable) = anim_table;
        select_sprite_entry(sprite,
            ((u8 *)anim_table)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)actor->flags1C) & ACTOR_ASLEEP) {
        if (sprite->frameTable == D_80157C90) {
            body->action_id.u = 0xD;
            body->action_phase.u = 1;
            body->unk_8C.word = 0;
            actor->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(body, context, sprite, D_80157CA0) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)actor->flags1C) & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(body, context, sprite, actor);
            return;
        }

        {
            u8 current_state = body->action_id.u;
            u32 idle_state = 0xE;
            void *current_anim;

            if (current_state != idle_state) {
                body->action_id.u = idle_state;
                body->unk_B4.halves.high.s = 0;
            }
            current_anim = sprite->frameTable;
            if (current_anim == D_80157CA8) {
                if (sprite->flags & 0xE000) {
                    (sprite->frameTable) = kewne_uncached_frame_set;
                    select_sprite_entry(sprite,
                        kewne_uncached_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                        0);
                    sprite->frame_ticks = 1;
                    body->unk_A0.parts.high = 0;
                    body->unk_9E.s = 0;
                }
            } else {
                void *idle_anim = kewne_uncached_frame_set;
                if (current_anim != idle_anim) {
                    (sprite->frameTable) = idle_anim;
                    select_sprite_entry(sprite,
                        *(u8 *)((((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7) + (u32)idle_anim),
                        0);
                    sprite->frame_ticks = 1;
                    body->unk_A0.parts.high = 0;
                    body->unk_9E.s = 0;
                }
            }
        }

        (*(u32 *)&actor->flags1C) |= 0x40000;
        body->action_state_flags &= 0xFFF7;

        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(body, context, sprite, D_80157C38) != 0) {
                return;
            }
        }

        if (((u32)actor->flags1C) & ACTOR_LIFTED) {
            s16 adjusted_offset;

            begin_actor_move_to_target_facing(body, context, sprite, actor);
            adjusted_offset = body->unk_90.parts.high.u - body->unk_A0.parts.high;
            body->unk_A0.parts.high = 0;
            body->unk_9E.s = 0;
            body->unk_90.parts.high.s = adjusted_offset;
            func_80157078(body, context, sprite, actor);
            return;
        }

        if ((can_entity_gain_level(actor) << 16) != 0) {
            process_selected_actor_record(body, context, sprite, actor);
        }
    }

    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;

    if (actor->pending_turn_updates > 0) {
        if (((u32)actor->flags1C) & ACTOR_PARALYZED) {
            update_actor_status_and_mp(actor);
            return;
        }
        if ( *(u16 *)&sprite->tile_x !=reference_tile_object.tile_position.word) {
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
                if ((func_801551CC(body, context, sprite, 0) << 16) == 0) {
                    return;
                }
                action = actor->action_flags | 0x4000;
                actor->action_flags = action;
            }

            if (actor->action_flags & ACTOR_ACTION_PENDING) {
                action = actor->action_flags & ACTOR_ACTION_CODE_MASK;
                switch (action) {
                case 8:
                case 9:
                    if ((func_80154E10(body, context, sprite, actor) << 16) != 0) {
                        return;
                    }
                    func_801550A8(body, context, sprite, actor);
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
                        &distance);
                    player = primary_actor_record;
                    actor->facing = facing;
                    if (player->action_id.u == 0x11) {
                        begin_actor_spell_action(body, context, sprite, D_80157C88, D_80153FA4);
                        return;
                    }
                }

                case 12:
                    update_actor_status_and_mp(actor);
                    return;

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(body, context, sprite, D_80157C88, D_80153FA4);
                    return;

                case 11:
                default:
                    break;
                }
            }
        }

        func_801546C8(body, context, sprite, actor);
        return;
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
