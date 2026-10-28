#include "shared/object_node.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"

typedef struct S_801741CC_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x4];
    u16 unk_AC;
} S_801741CC_0;   /* arg0 in update_actor_action_and_flags */

extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
#include "dungeon/player/object/action_state.h"
extern void on_actor_status_updated(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void func_80174520(void *, void *, void *, void *);

#include "dungeon/monster/cyclone.h"
extern u8 cyclone_frame_set_1[];

/* Update the actor action state, directional animation, and entity flags. */
void update_actor_action_and_flags(ActorRecord *actor, ObjectPosition *action_ctx, SpriteFrameState *anim, ActorRecord *entity) {
    s32 action_state;

    action_state = actor->action_phase.u;
    switch (action_state) {
    case 0:
    {
        u8 *direction_anims;

        if (!(anim->flags & 0xE000)) {
            return;
        }

        g_dungeon_status.activity_counts.parts.pending_action_count--;
        direction_anims = cyclone_direction_frames;
        (anim->frameTable) = direction_anims;
        select_sprite_entry(anim,
            direction_anims[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        actor->action_phase.u++;
        return;
    }

    case 1:
    {
        u32 entity_flags;

        if (entity->mp_value.parts.whole != 0) {

            (anim->frameTable) = cyclone_frame_set_1;
            select_sprite_entry(anim,
                cyclone_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
            entity->flags1C |= 0x40000;
            g_dungeon_status.activity_counts.parts.pending_action_count++;
            actor->action_phase.u++;
            return;
        }

        if (g_dungeon_status.flags & 0x1000) {
            return;
        }

        if (entity->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, action_ctx, anim, 0) != 0) {
                return;
            }
        }

        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
            return;
        }

        entity_flags = ((u32)entity->flags1C);
        if (entity_flags & 0x100) {
            begin_pushed_actor_move(actor, action_ctx, anim, entity);
            return;
        }

        if (entity_flags & 0x80000) {
            u16 stat_value;
            u16 stat_delta;

            begin_actor_move_to_target_facing(actor, action_ctx, anim, entity);
            stat_value = actor->unk_90.parts.high.u;
            stat_delta = ((S_801741CC_0 *)actor)->unk_A6;
            ((S_801741CC_0 *)actor)->unk_A6 = 0;
            ((S_801741CC_0 *)actor)->unk_AC = 0;
            actor->unk_90.parts.high.u = stat_value - stat_delta;
            func_80174520(actor, action_ctx, anim, entity);
            return;
        }

        if (entity->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(entity) << 16) != 0) {
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

        update_actor_status_and_mp(entity);
        on_actor_status_updated(entity);
        if (entity->mp_value.parts.whole == 0) {
            return;
        }

        (anim->frameTable) = cyclone_frame_set_1;
        select_sprite_entry(anim,
            cyclone_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        entity->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }

        actor->action_phase.u++;
        return;
    case 2:
        if (anim->flags & 0xE000) {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
            entity->flags1C &= ~ACTOR_MP_EMPTY;
            actor->unk_8C.address = update_actor_animation;
        }

        return;
    }
}
