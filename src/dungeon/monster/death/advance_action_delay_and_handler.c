#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173A14_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173A14_0;   /* arg0 in advance_action_delay_and_handler */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern s32 death_action_resume_address;
extern s32 D_8017466C;

/* Advance the action delay, reset motion, and select the next handler. */
void advance_action_delay_and_handler(S_80173A14_0 *action, ObjectPosition *motion, SpriteFrameState *action_info, EntityRec *actor_data)
{
    s16 delay;
    s32 tracked_actor;

    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(actor_data);
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        action->unk_9B++;

        if (actor_data->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, action_info, &D_8017466C);
            return;
        }
        if (action_info->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (actor_data->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            delay = 8;
        } else {
            delay = -1;
        }
        action->unk_96.s = delay;
                        /* fall through */

    case 1:
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (action_info->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (actor_data->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, action_info, &D_8017466C);
            return;
        } else {
            action->unk_96.s = 2;
            action->unk_9B++;
        }
        return;

    case 2:
        if (action->unk_96.s != 0) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
        }
        delay = action->unk_96.u - 1;
        action->unk_96.s = delay;
        if ((s32)(delay << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, action_info->unk_24, action_info->unk_25);

        tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_actor == (s32)((u8 *)actor_data - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
        }
        action->unk_8C = &death_action_resume_address;
        return;

    default:
        return;
    }
}
