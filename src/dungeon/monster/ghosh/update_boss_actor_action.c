#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/actor_action_flags.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

#include "engine/graphics/select_sprite_entry_api.h"         /* extern */
#include "dungeon/actor/motion.h"
struct ActorRecord; s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);                     /* extern */
s32 find_active_rect_containing_point(s32 point_x, s32 point_y);                           /* extern */
void update_actor_status_and_mp(struct ActorRecord *);                      /* extern */
s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames); /* extern */
struct Rec_func_800A9E70_arg0; struct Rec_func_800AA258_arg2; void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor); /* extern */
void func_8016FA84(void *actor, void *action, SpriteFrameState *entity, void *path_arg);                            /* extern */
void advance_boss_actor_movement_state(void *, void *, void *, void *); /* extern */
struct Rec_func_800A9E70_arg0; s32 update_boss_action_result(ActorRecord *, s32, s32, s16); /* extern */
void func_8017092C(ActorRecord *object, ObjectPosition *unused_1, SpriteFrameState *unused_2, ActorRecord *flag_owner); /* extern */
s32 advance_boss_command_stream(void *object_arg, void *context_arg, void *entity_arg);     /* extern */
#include "dungeon/monster/ghosh.h"
extern u8 D_80174A64[];

/* Updates actor state, directional animation, and action handling. */
void update_boss_actor_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity) {
    u8 stack_pad[8];
    u8 current_state;
    s32 next_state;

    if (g_dungeon_status.flags & 0x1000) {
        actor->action_id.u = 0xEU;
        func_8016FA84(actor, context, sprite, entity);
        return;
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags1C & ACTOR_PUSH_PENDING) {
            begin_pushed_actor_move(actor, context, sprite, entity);
            return;
        }
        current_state = actor->action_id.u;
        next_state = 0xE;
        if (current_state != next_state) {
            if (*(u8 * *)&sprite->frameTable != ghosh_direction_frames) {
                sprite->frameTable = ghosh_direction_frames;
                select_sprite_entry(sprite, ghosh_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            }
            actor->action_id.u = next_state;
        }
        actor->action_state_flags = (u16) (actor->action_state_flags & 0xFFF3);
        if (!((entity->hp_delta == 0) || (begin_ready_actor_directional_action(actor, context, sprite, D_80174A64) == 0))) {
            return;
        }
        if (entity->flags1C & ACTOR_LIFTED) {
            begin_actor_move_to_target_facing(actor, context, sprite, entity);
            func_8017092C(actor, context, sprite, entity);
            sprite->frameTable = ghosh_direction_frames;
            select_sprite_entry(sprite, ghosh_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7], 0);
            actor->unk_90.value = 0;
            return;
        }
    }
    sprite->room_index = find_active_rect_containing_point(sprite->tile_x,
        sprite->tile_y);
    if (entity->pending_turn_updates > 0) {
        if (entity->flags1C & ACTOR_PARALYZED) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (!(entity->action_flags & ACTOR_ACTION_PENDING)) {
            if (!(g_dungeon_status.flags & 0x2000) || ((check_entity_relation(entity, (struct ActorRecord *)(((u8 *)primary_actor_record->previous_actor_header) + 0x20)) << 0x10)
                == 0)) {
                if (system_update_flags & 8) {
                    advance_boss_command_stream(actor, context, sprite);
                    entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
                    update_actor_status_and_mp(entity);
                    entity->action_flags = (u16) (entity->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
                    return;
                }
                if ((update_boss_action_result(actor, (s32)(context), (s32)(sprite), 0) << 0x10) == 0) {
                    return;
                }
                entity->action_flags = (u16) (entity->action_flags | 0x4000);
            } else {
                return;
            }
        }
        entity->action_flags = (u16) (entity->action_flags & ACTOR_ACTION_CLEAR_PENDING_MASK);
        entity->movement_queue_state = (u8) (entity->movement_queue_state & 0x7F);
        update_actor_status_and_mp(entity);
        advance_boss_actor_movement_state(actor, context, sprite, entity);
    }
}
