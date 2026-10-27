#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
#include "dungeon/player/object/action_state.h"
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(void *);
extern void begin_pushed_actor_move(void *,void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern void update_timed_effect_size_and_position(void *, s32, void *, void *);

#include "dungeon/monster/saber.h"

extern u8 saber_action_direction_frames[];

typedef struct S_801740DC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801740DC_0;   /* arg0 in update_actor_directional_animation */

/* Updates actor state, directional animation, and the shared transition counter. */
void update_actor_directional_animation(void *actor_in, void *actor_index, SpriteFrameState *target, void *entity_in)
{
    EntityRec *entity = entity_in;
    s32 state;
    s32 entity_flags;
    s32 direction;
    DungeonGlobalStatus *shared_state;
    state = ((S_801740DC_0 *)actor_in)->unk_9B;
    switch (state) {
    case 0:
    if (!(target->flags & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    target->frameTable = saber_direction_frames_2;
    direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
    select_sprite_entry(target, saber_direction_frames_2[direction & 7], 0);
    ((S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 1:
    if (entity->tileY != 0) {
        DungeonGlobalStatus *shared_counter;

        target->frameTable = saber_action_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, saber_action_direction_frames[direction & 7], 0);
        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count++;
        ((S_801740DC_0 *)actor_in)->unk_9B++;
        return;
    } else {
        shared_state = &g_dungeon_status;
        if (shared_state->flags & 0x1000) {
            return;
        }
        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor_in, actor_index, target, 0) != 0) {
                return;
            }
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }
        entity_flags = entity->flags1C;
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor_in, actor_index, target, entity);
            return;
        }
        if (entity_flags & 0x80000) {
            begin_actor_move_to_target_facing(actor_in, actor_index, target, entity);
            update_timed_effect_size_and_position(actor_in, actor_index, target, entity);
            return;
        }
        if (entity->unk_6D == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            if ((check_entity_relation(entity,
                    (u8 *)primary_actor_record->previous_actor_header + 0x20) << 16) != 0) {
                return;
            }
            update_actor_status_and_mp(entity);
        } else {
            update_actor_status_and_mp(entity);
        }
        on_actor_status_updated(entity);
        if (entity->tileY == 0) {
            return;
        }
        target->frameTable = saber_action_direction_frames;
        direction = (g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9;
        select_sprite_entry(target, saber_action_direction_frames[direction & 7], 0);
        shared_state->activity_counts.parts.pending_action_count++;
    }
    ((S_801740DC_0 *)actor_in)->unk_9B++;
    return;

    case 2:
    if (!(target->flags & 0xE000)) {
        return;
    }
    {
        DungeonGlobalStatus *shared_counter;

        shared_counter = &g_dungeon_status;
        shared_counter->activity_counts.parts.pending_action_count--;
    }
    ((S_801740DC_0 *)actor_in)->unk_8C = &saber_behavior_entry;

    return;
    default:
        return;
    }
}
