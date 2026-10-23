#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/actor_action.h"

   /* arg0 in advance_actor_timed_transition */

extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);
extern s32 weadog_action_resume_address;

/* Advance a timed entity state transition, clearing motion and updating its handler. */
void advance_actor_timed_transition(ActorActionTimerView *controller, ObjectPosition *motion, SpriteFrameState *actor, EntityRec *entity_data)
{
    s32 state;
    s32 timer_signed;
    s32 timer_unsigned;
    s32 timer_next;
    s32 timer_init;

    state = controller->phase;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity_data);
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        controller->phase++;

        if (entity_data->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, actor, 0);
            return;
        }
        if (actor->flags & 0x8000) {
            controller->timer.u = 0;
            controller->phase = 2;
            return;
        }

        timer_init = -1;
        if (entity_data->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer_init = 8;
        }
        controller->timer.u = timer_init;
    case 1:
        timer_signed = controller->timer.s;
        timer_unsigned = controller->timer.u;
        if (timer_signed > 0) {
            controller->timer.u = timer_unsigned - 1;
        } else if (actor->flags & 0x6000) {
            controller->timer.u = 0;
        }

        if (controller->timer.s != 0) {
            return;
        }
        if (entity_data->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(controller, motion, actor, 0);
            return;
        }
        controller->timer.u = 1;
        controller->phase++;
        return;
    case 2:
        timer_next = controller->timer.u - 1;
        controller->timer.u = timer_next;
        if ((timer_next << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);

        if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)entity_data - 0x20)) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        controller->next_action = &weadog_action_resume_address;

        return;
    default:
        return;
    }
}
