#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172DB4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172DB4_0;   /* arg0 in update_decaying_movement_and_alignment */

extern void set_record_integer_tile_center();
extern void begin_actor_display_action();
extern void apply_clamped_actor_value_delta();

extern s32 D_80170E9C;
extern s32 D_80174F18;

/* Updates decaying movement and tile alignment before advancing or finishing the action. */
void update_decaying_movement_and_alignment(S_80172DB4_0 *action, ObjectPosition *motion, SpriteFrameState *tile_state, EntityRec *actor_data)
{
    s16 timer;
    s32 tracked_actor;

    switch (action->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(actor_data);
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                     ((actor_data->unk_6A >> 8) & 0xE)) << 19;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                     ((actor_data->unk_6A >> 8) & 0xE)) << 19;
        action->unk_9B++;

        if (actor_data->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile_state, &D_80174F18);
            return;
        }
        if (tile_state->flags & 0x8000) {
            action->unk_96.s = 0;
            action->unk_9B = 2;
            return;
        }
        if (actor_data->flags1C & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        action->unk_96.s = timer;
                        /* fall through */

    case 1:
    {
        s32 velocity_x = motion->velocity_x;
        motion->velocity_x = velocity_x - velocity_x / 4;
    }
        {
            s32 velocity_y = motion->velocity_y;
            motion->velocity_y = velocity_y - velocity_y / 4;
        }
        if (action->unk_96.s > 0) {
            action->unk_96.s = action->unk_96.u - 1;
        } else if (tile_state->flags & 0x6000) {
            action->unk_96.s = 0;
        }
        if (action->unk_96.s != 0) {
            return;
        }
        if (actor_data->unk_28 != 0) {
            action->unk_96.s = 8;
            action->unk_9B++;
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        begin_actor_display_action(action, motion, tile_state, &D_80174F18);
        return;

    case 2:
        timer = action->unk_96.s;
        if (timer > 0) {
            {
                s32 target_pos = tile_state->unk_24 << 6;
                s32 current_pos = motion->x.w.i - 0x20;
                motion->velocity_x =
                    ((target_pos - current_pos) << 16) / timer;
            }
            {
                s32 target_pos = tile_state->unk_25 << 6;
                s32 current_pos = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_pos - current_pos) << 16) / action->unk_96.s;
            }
        }
        timer = action->unk_96.u - 1;
        action->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        if ((tile_state->flags & 0x6000) &&
            ((EntityRec *)actor_data)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, tile_state, &D_80174F18);
            return;
        } else {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            set_record_integer_tile_center(motion, tile_state->unk_24, tile_state->unk_25);

            tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
            if (tracked_actor == (s32)((u8 *)actor_data - 0x20)) {
                g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
            }
            action->unk_8C = &D_80170E9C;
            return;
        }

    default:
        return;
    }
}
