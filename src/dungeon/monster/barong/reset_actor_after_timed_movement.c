#include "common.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

typedef struct S_801738B8_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
} S_801738B8_0;   /* object in reset_actor_after_timed_movement */

typedef struct S_801738B8_1 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_801738B8_1;   /* room in reset_actor_after_timed_movement */


extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

extern u8 D_801716F4[];
#include "dungeon/monster/barong.h"
extern u8 D_80175564[];
extern u8 D_8017558C[];

/* Updates timed movement, returns the actor to its tile, and resets its action state. */
void reset_actor_after_timed_movement(void *object_arg, void *motion_arg, void *actor_arg, void *room_arg)
{
    void *object = object_arg;
    ObjectPosition *motion = motion_arg;
    SpriteFrameState *actor= actor_arg;
    void *room = room_arg;
    s16 timer;
    u16 old_timer;
    s32 room_ref;

    switch (((S_801738B8_0 *)object)->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(room);
        ((S_801738B8_0 *)object)->unk_96.s = 4;
        ((S_801738B8_0 *)object)->unk_9B++;
        if (((S_801738B8_1 *)room)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(object, motion, actor, D_8017558C);
            return;
        }
        if (!(actor->flags & 0x8000)) {
            return;
        }
        ((S_801738B8_0 *)object)->unk_96.s = 0;
        ((S_801738B8_0 *)object)->unk_9B = 3;
        return;

    case 1:
        timer = ((S_801738B8_0 *)object)->unk_96.u - 1;
        ((S_801738B8_0 *)object)->unk_96.s = timer;
        if (timer > 0) {
            motion->velocity_x =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                    ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 19;
            motion->velocity_y =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                    ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 19;
            return;
        }
        if (timer != 0) {
            return;
        }
        motion->velocity_x =
            *(s16 *)((u8 *)((s8 *)dir_step_x) +
                ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 18;
        motion->velocity_y =
            *(s16 *)((u8 *)((s8 *)dir_step_y) +
                ((((S_801738B8_1 *)room)->unk_6A >> 8) & 0xE)) << 18;
        ((S_801738B8_0 *)object)->unk_96.s = 6;
        ((S_801738B8_0 *)object)->unk_9B++;
        return;

    case 2:
        if (((S_801738B8_1 *)room)->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(object, motion, actor, D_8017558C);
            return;
        }

        timer = ((S_801738B8_0 *)object)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_coord = actor->unk_24 << 6;
                s32 current_coord = motion->x.w.i - 0x20;

                motion->velocity_x =
                    ((target_coord - current_coord) << 16) / timer;
            }
            {
                s32 target_coord = actor->unk_25 << 6;
                s32 current_coord = motion->y.w.i - 0x20;

                motion->velocity_y =
                    ((target_coord - current_coord) << 16) /
                    ((S_801738B8_0 *)object)->unk_96.s;
            }
        }
        old_timer = ((S_801738B8_0 *)object)->unk_96.u;
        ((S_801738B8_0 *)object)->unk_96.s = old_timer - 1;
        if ((s32)(old_timer << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        ((S_801738B8_0 *)object)->unk_9B++;
        return;

    case 3:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->unk_24, actor->unk_25);
        if (actor->frameTable == D_80175564) {
            (actor->frameTable) = barong_direction_frames;
            select_sprite_entry(actor,
                barong_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801738B8_1 *)room)->unk_2A + 0x100)
                    >> 9) & 7], 0);
        }
        room_ref = ((s32)g_dungeon_status.pending_display_owner);
        if (room_ref == (s32)((u8 *)room - 0x20)) {
            g_dungeon_status.pending_display_owner = room_ref & 0x7FFFFFFF;
        }
        ((S_801738B8_0 *)object)->unk_8C = D_801716F4;
        ((S_801738B8_0 *)object)->unk_9A = 0xE;
        return;

    default:
        return;
    }
}

/* MECHANISM: Ordered $s0-$s3 argument locals reproduce the retail save/move prologue.
   Duplicated state increments keep the predecessor-local lbu alive, while scoped
   coord/current temporaries expose the second lh to fill the mflo hazard slot.
   The paired +1/-1 shapes cancel the displacement cascade at 2.8.1-G0. */
