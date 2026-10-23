#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172CE0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172CE0_0;   /* arg0 in return_actor_to_tile_center */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern s32 garuda_action_resume_address;
extern s32 D_801748C0;

/* Applies backward motion, then returns the actor to its tile center or starts the next action. */
void return_actor_to_tile_center(S_80172CE0_0 *action, ObjectPosition *motion, SpriteFrameState *entity, EntityRec *actor)
{
    s16 frames_left;
    s32 tracked_actor;

    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        motion->velocity_x =
            -((s16 *)((s8 *)dir_step_x))[((u16)((s16)actor->unk_6A) >> 9) & 7] << 15;
        motion->velocity_y =
            -((s16 *)((s8 *)dir_step_y))[((u16)((s16)actor->unk_6A) >> 9) & 7] << 15;
        action->unk_9B++;

        if (actor->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, entity, &D_801748C0);
            return;
        }
        if (entity->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (actor->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            frames_left = 8;
        } else {
            frames_left = -1;
        }
        action->unk_96.s = frames_left;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;

    case 1:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[((u16)((s16)actor->unk_6A) >> 9) & 7] << 10;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[((u16)((s16)actor->unk_6A) >> 9) & 7] << 10;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (entity->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (actor->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, entity, &D_801748C0);
            return;
        } else {
            action->unk_96.s = 8;
            action->unk_9B++;
        }
        return;

    case 2:
        frames_left = action->unk_96.s;
        if (frames_left != 0) {
            {
                s32 target_x = entity->tile_x << 6;
                s32 current_x = motion->x.w.i - 0x20;

                motion->velocity_x =
                    ((target_x - current_x) << 15) / frames_left;
            }
            {
                s32 target_y = entity->tile_y << 6;
                s32 current_y = motion->y.w.i - 0x20;

                motion->velocity_y =
                    ((target_y - current_y) << 15) /
                    action->unk_96.s;
            }
        }
        frames_left = action->unk_96.u - 1;
        action->unk_96.s = frames_left;
        if ((s32)(frames_left << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, entity->tile_x, entity->tile_y);

        tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
        }
        action->unk_8C = &garuda_action_resume_address;
        return;

    default:
        return;
    }
}
