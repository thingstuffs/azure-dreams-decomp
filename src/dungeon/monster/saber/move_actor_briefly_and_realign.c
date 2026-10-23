#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173964_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173964_0;   /* arg0 in move_actor_briefly_and_realign */

extern void select_sprite_entry(void *, s32, s32);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void begin_actor_display_action(void *actor, void *unused, void *display, u8 *facing_variants);
extern void apply_clamped_actor_value_delta(void *);

#include "dungeon/monster/saber.h"

extern u8 D_80174DFC[];
extern u8 D_80174E24[];

/* Applies a brief directional movement, then returns the actor to its grid position. */
void move_actor_briefly_and_realign(void *action, ObjectPosition *motion, SpriteFrameState *actor, EntityRec *entity)
{
    s32 state;
    s16 timer;
    u16 timer_bits;
    u8 next_state;
    s32 target_x;
    s32 current_x;
    s32 target_y;
    s32 current_y;
    s32 tracked_entity;

    state = ((S_80173964_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        ((S_80173964_0 *)action)->unk_96.s = 12;
        ((S_80173964_0 *)action)->unk_9B++;
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, actor, D_80174E24);
            return;
        }
        if (actor->flags & 0x8000) {
            ((S_80173964_0 *)action)->unk_96.s = 0;
            ((S_80173964_0 *)action)->unk_9B = 3;
        }
        return;

    case 1:
        timer_bits = ((S_80173964_0 *)action)->unk_96.u - 1;
        ((S_80173964_0 *)action)->unk_96.u = timer_bits;
        timer = timer_bits;
        if (timer >= 11) {
            motion->velocity_x =
                *(s16 *)((u8 *)((s8 *)dir_step_x) +
                         ((entity->unk_6A >> 8) & 0xE)) << 20;
            motion->velocity_y =
                *(s16 *)((u8 *)((s8 *)dir_step_y) +
                         ((entity->unk_6A >> 8) & 0xE)) << 20;
            actor->flags |= 0x800;
            return;
        }
        if (timer >= 7) {
            motion->velocity_x /= 4;
            motion->velocity_y /= 4;
            return;
        }
        if (timer >= 2) {
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            return;
        }
        if (timer == state) {
            actor->flags &= 0xF7FF;
            return;
        }
        if (timer != 0) {
            return;
        }
        next_state = ((S_80173964_0 *)action)->unk_9B;
        timer = 4;
        ((S_80173964_0 *)action)->unk_96.s = timer;
        ((S_80173964_0 *)action)->unk_9B = next_state + 1;
        return;

    case 2:
        if (entity->unk_28 == 0) {
            motion->velocity_z = 0;
            motion->velocity_y = 0;
            motion->velocity_x = 0;
            begin_actor_display_action(action, motion, actor, D_80174E24);
            return;
        }
        timer = ((S_80173964_0 *)action)->unk_96.s;
        if (timer != 0) {
            target_x = actor->tile_x << 6;
            current_x = motion->x.w.i - 0x20;
            motion->velocity_x = ((target_x - current_x) << 16) / timer;
            target_y = actor->tile_y << 6;
            current_y = motion->y.w.i - 0x20;
            motion->velocity_y =
                ((target_y - current_y) << 16) / ((S_80173964_0 *)action)->unk_96.s;
        }
        timer_bits = ((S_80173964_0 *)action)->unk_96.u;
        ((S_80173964_0 *)action)->unk_96.u = timer_bits - 1;
        if ((s32)(timer_bits << 16) > 0) {
            return;
        }
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        next_state = ((S_80173964_0 *)action)->unk_9B;
        ((S_80173964_0 *)action)->unk_9B = next_state + 1;
        return;
    case 3:
        motion->velocity_z = 0;
        motion->velocity_y = 0;
        motion->velocity_x = 0;
        set_record_integer_tile_center(motion, actor->tile_x, actor->tile_y);
        if (actor->frameTable == D_80174DFC) {
            actor->frameTable = saber_direction_frames;
            select_sprite_entry(
                actor,
                saber_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                0);
        }
        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner = tracked_entity & 0x7FFFFFFF;
        }
        ((S_80173964_0 *)action)->unk_8C = &saber_behavior_entry;

        return;
    default:
        return;
    }
}

/* MECHANISM: Four live arguments naturally produce the 0x28 frame and s1/s0/s2/s3 save roles.
   A distinct u8 next_state plus timer-held constant 4 fixes v0/v1 lifetimes and the bgtz store slot.
   The named D_80083460 pointer forces retail's split lui/addiu base before the final field load. */
