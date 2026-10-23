#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/griffon.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80167234_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80167234_0;   /* arg0 in advance_directional_motion_to_center */


extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_80164E7C;
extern u8 D_80168C44[];
extern u8 D_80168C74[];

/* Advance directional motion and settle the actor at its tile center. */
void advance_directional_motion_to_center(void *motion_state, ObjectPosition *motion, SpriteFrameState *sprite, void *actor)
{
    s32 state;
    s16 timer;
    s32 tracked_actor;

    state = ((S_80167234_0 *)motion_state)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        motion->velocity_x =
            -((s16 *)((s8 *)dir_step_x))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 15;
        motion->velocity_y =
            -((s16 *)((s8 *)dir_step_y))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 15;
        ((S_80167234_0 *)motion_state)->unk_9B++;

        if (((EntityRec *)actor)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, sprite, D_80168C74);
            return;
        }
        if (sprite->flags & 0x8000) {
            ((S_80167234_0 *)motion_state)->unk_96.s = 0;
            ((S_80167234_0 *)motion_state)->unk_9B = 3;
            return;
        }

        if (((u32)((EntityRec *)actor)->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_80167234_0 *)motion_state)->unk_96.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;
                        /* fall through */

    case 1:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;

        if (((S_80167234_0 *)motion_state)->unk_96.s > 0) {
            ((S_80167234_0 *)motion_state)->unk_96.s = ((S_80167234_0 *)motion_state)->unk_96.u - 1;
        } else if (sprite->flags & 0x6000) {
            ((S_80167234_0 *)motion_state)->unk_96.s = 0;
        }

        if (((S_80167234_0 *)motion_state)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, sprite, D_80168C74);
            return;
        }
        sprite->frameTable = D_80168C44;
        select_sprite_entry(
            sprite,
            D_80168C44[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80167234_0 *)motion_state)->unk_9B++;
        return;

    case 2:
        motion->velocity_x +=
            ((s16 *)((s8 *)dir_step_x))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;
        motion->velocity_y +=
            ((s16 *)((s8 *)dir_step_y))[(((EntityRec *)actor)->unk_6A >> 9) & 7] << 14;
        if (!(sprite->flags & 0x6000)) {
            return;
        }

        sprite->frameTable = D_80168C44;
        select_sprite_entry(
            sprite,
            D_80168C44[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_80167234_0 *)motion_state)->unk_96.s = 8;
        ((S_80167234_0 *)motion_state)->unk_9B++;
        return;

    case 3:
        timer = ((S_80167234_0 *)motion_state)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = sprite->unk_24 << 6;
                s32 current_x = motion->x.w.i - 0x20;
                motion->velocity_x = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = sprite->unk_25 << 6;
                s32 current_y = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_y - current_y) << 15) / ((S_80167234_0 *)motion_state)->unk_96.s;
            }
        }

        timer = ((S_80167234_0 *)motion_state)->unk_96.u - 1;
        ((S_80167234_0 *)motion_state)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.v = ((sprite->unk_24 << 6) + 0x20) << 16;
        motion->y.v = ((sprite->unk_25 << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);

        tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
        }
        ((S_80167234_0 *)motion_state)->unk_8C = &D_80164E7C;
    }
}
