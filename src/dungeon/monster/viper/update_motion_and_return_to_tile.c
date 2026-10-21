#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8017345C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017345C_1;   /* arg0 in update_motion_and_return_to_tile */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern u8 D_80170E94;
extern u8 D_80174ABC[];

/* Updates directional motion and returns the entity to its tile when the timer expires. */
void update_motion_and_return_to_tile(S_8017345C_1 *action, ObjectPosition *motion, SpriteFrameState *tile, EntityRec *entity)
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
            begin_actor_display_action(action, motion, tile, D_80174ABC);
            return;
        }
        if (tile->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (entity->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x -=
            ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -=
            ((s16 *)((s8 *)dir_step_y))[direction] << 14;
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
            begin_actor_display_action(action, motion, tile, D_80174ABC);
            return;
        }
        action->unk_96.s = 8;
        action->unk_9B++;
        return;

    case 2:
        timer = action->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = tile->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->velocity_x =
                    ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = tile->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_y - current_y) << 15) /
                    action->unk_96.s;
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
        set_record_integer_tile_center(motion, tile->unk_24,
                      tile->unk_25);

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        action->unk_8C = &D_80170E94;
        return;

    default:
        return;
    }
}
