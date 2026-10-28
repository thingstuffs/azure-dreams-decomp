#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/monster/grineut.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/player/object.h"

typedef struct S_8015B238_1 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8015B238_1;   /* arg0 in settle_directional_actor_motion */


extern void select_sprite_entry(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, SpriteFrameState *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 grineut_slot_c_action_callback;
extern u8 grineut_frame_set_9[];
extern u8 D_8015C178[];

/* Updates directional movement and settles the actor at its tile center. */
void settle_directional_actor_motion(void *motion_state, ObjectPosition *motion, SpriteFrameState *map_actor, void *actor)
{
    s32 state;
    s32 direction;
    s16 timer;
    s32 tracked_actor;

    direction = (((EntityRec *)actor)->unk_6A >> 9) & 7;
    state = ((S_8015B238_1 *)motion_state)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(actor);
        motion->velocity_x = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        motion->velocity_y = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        ((S_8015B238_1 *)motion_state)->unk_9B++;

        if (((EntityRec *)actor)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, map_actor, D_8015C178);
            return;
        }
        if (map_actor->flags & 0x8000) {
            ((S_8015B238_1 *)motion_state)->unk_96.s = 0;
            ((S_8015B238_1 *)motion_state)->unk_9B = 3;
            return;
        }

        if (((u32)((EntityRec *)actor)->flags1C) & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((S_8015B238_1 *)motion_state)->unk_96.s = timer;

        motion->velocity_x -= motion->velocity_x / 4;
        motion->velocity_y -= motion->velocity_y / 4;

    case 1:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (((S_8015B238_1 *)motion_state)->unk_96.s > 0) {
            ((S_8015B238_1 *)motion_state)->unk_96.s = ((S_8015B238_1 *)motion_state)->unk_96.u - 1;
        } else if (map_actor->flags & 0x6000) {
            ((S_8015B238_1 *)motion_state)->unk_96.s = 0;
        }

        if (((S_8015B238_1 *)motion_state)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)actor)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(motion_state, motion, map_actor, D_8015C178);
            return;
        } else {
            map_actor->frameTable = grineut_frame_set_9;
            select_sprite_entry(
                map_actor,
                grineut_frame_set_9[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((S_8015B238_1 *)motion_state)->unk_9B++;
            return;
        }

    case 2:
        motion->velocity_x -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        motion->velocity_y -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (!(map_actor->flags & 0x6000)) {
            return;
        }

        map_actor->frameTable = grineut_frame_set_9;
        select_sprite_entry(
            map_actor,
            grineut_frame_set_9[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((S_8015B238_1 *)motion_state)->unk_96.s = 8;
        ((S_8015B238_1 *)motion_state)->unk_9B++;
        return;

    case 3:
        timer = ((S_8015B238_1 *)motion_state)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_coord = map_actor->tile_x << 6;
                s32 current_coord = motion->x.w.i - 0x20;
                motion->velocity_x = ((target_coord - current_coord) << 15) / timer;
            }
            {
                s32 target_coord = map_actor->tile_y << 6;
                s32 current_coord = motion->y.w.i - 0x20;
                motion->velocity_y =
                    ((target_coord - current_coord) << 15) / ((S_8015B238_1 *)motion_state)->unk_96.s;
            }
        }

        timer = ((S_8015B238_1 *)motion_state)->unk_96.u - 1;
        ((S_8015B238_1 *)motion_state)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        motion->x.v = ((map_actor->tile_x << 6) + 0x20) << 16;
        motion->y.v = ((map_actor->tile_y << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, map_actor->tile_x, map_actor->tile_y);

        tracked_actor = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_actor == (s32)((u8 *)actor - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_actor & 0x7FFFFFFF;
        }
        ((S_8015B238_1 *)motion_state)->unk_8C = &grineut_slot_c_action_callback;

        return;
    default:
        return;
    }
}
