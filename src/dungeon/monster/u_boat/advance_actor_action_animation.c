#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"

typedef struct S_80174788_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} S_80174788_0;   /* arg0 in advance_actor_action_animation */

extern s32 check_entity_relation();
#include "dungeon/player/object/action_state.h"
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void update_actor_action_transition(void *state, ObjectPosition *update_mode, SpriteFrameState *sprite, void *entity);

extern u8 uboat_action_frames[];
extern u8 u_boat_motion_frames[];
#include "dungeon/monster/u_boat.h"
#include "engine/graphics.h"
#include "dungeon/actor.h"

/* Advance an actor action through animation completion and status checks. */
void advance_actor_action_animation(ActorRecord *action, ObjectPosition *actor_index, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 action_state;
    u16 reset_offset;
    u16 value_before_reset;
    s32 actor_flags;

    action_state = action->action_phase.u;
    switch (action_state) {
    case 0:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        (sprite->frameTable) = uboat_action_frames;
        select_sprite_entry(sprite,
                      uboat_action_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        action->action_phase.u++;
        return;

    case 1:
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if (actor->hp_delta != 0) {
            if (begin_ready_actor_directional_action(action, actor_index, sprite, 0) != 0) {
                return;
            }
        }
        /*
         * BUG: after a Mazarr seed restores MP, this waits on the pending EXP owner, which can be this U-Boat
         * itself. Allow its own pending level-up to proceed.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            return;
        }
        actor_flags = actor->flags1C;
        if (actor_flags & 0x100) {
            begin_pushed_actor_move(action, actor_index, sprite, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            begin_actor_move_to_target_facing(action, actor_index, sprite, actor);
            value_before_reset = action->unk_90.parts.high.u;
            reset_offset = action->unk_A0.parts.high;
            action->unk_A0.parts.high = 0;
            action->unk_9E.s = 0;
            action->unk_90.parts.high.u = value_before_reset - reset_offset;
            update_actor_action_transition(action, actor_index, sprite, actor);
            return;
        }
        if (actor->pending_turn_updates == 0) {
            return;
        }
        if ((has_pending_actor_or_turn_action(actor) << 16) != 0) {
            if ((check_entity_relation(actor, ((s32)primary_actor_record->previous_actor_header) + 0x20) << 16) != 0) {
                return;
            }
        }
        update_actor_status_and_mp(actor);
        on_actor_status_updated(actor);
        if (actor->mp_value.parts.whole == 0) {
            return;
        }
        (sprite->frameTable) = u_boat_motion_frames;
        select_sprite_entry(sprite,
                      u_boat_motion_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
                      0);
        actor->flags1C |= 0x40000;
        g_dungeon_status.activity_counts.parts.pending_action_count++;

        action->action_phase.u++;
        return;

    case 2:
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        {

            g_dungeon_status.activity_counts.parts.pending_action_count--;
        }
        actor->flags1C &= ~ACTOR_MP_EMPTY;
        action->unk_8C.address = uboat_behavior_entry;

        return;
    }
}
