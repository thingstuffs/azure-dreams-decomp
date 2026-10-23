#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801732B4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801732B4_1;   /* arg0 in update_motion_and_recenter_entity */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern s32 mandara_action_resume_address;
extern s32 D_80175268;

/* Updates directional motion, then recenters the entity on its tile and finishes the action. */
void update_motion_and_recenter_entity(S_801732B4_1 *action, ObjectPosition *motion, SpriteFrameState *tile, EntityRec *entity)
{
    s16 timer;
    s32 tracked_entity;
    s32 direction;

    direction = (entity->unk_6A >> 9) & 7;

    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->velocity_x = ((s16 *)((s8 *)dir_step_x))[direction] << 17;
        motion->velocity_y = ((s16 *)((s8 *)dir_step_y))[direction] << 17;
        action->unk_9B++;

        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile, &D_80175268);
            return;
        }
        if (tile->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (entity->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile, &D_80175268);
            return;
        }
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        if (action->unk_96.s != 0) {
            {
                s32 target_x;
                s32 current_x;

                target_x = tile->tile_x << 6;
                current_x = motion->x.w.i - 0x20;
                motion->velocity_x =
                    ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_z;
                s32 current_z;

                target_z = tile->tile_y << 6;
                current_z = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_z - current_z) << 15) >> 1;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, tile->tile_x, tile->tile_y);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &mandara_action_resume_address;
        return;

    default:
        return;
    }
}
