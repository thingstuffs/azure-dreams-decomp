#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "sdk/libgte.h"


typedef struct S_800AB538_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
    u16 unk_8A;
} S_800AB538_1;   /* p3 in update_actor_hop_and_shrink */



extern u8 view_reference_entity[];
extern s16 actor_hop_target_height;

/* Move toward the target while shrinking, then mark the animation complete. */
s32 update_actor_hop_and_shrink(void *animation, ObjectPosition *motion, SpriteFrameState *scale, void *render_arg)
{
    S_800AB538_1 *render = render_arg;
    s32 move_frames;
    s16 frames_left;
    s32 height_offset;
    u16 scale_value;
    s32 state;
    s32 next_state;

    state = ((ActorRecord *)animation)->action_phase.u;
    switch (state) {
    case 0:
        ((ActorRecord *)animation)->action_timer.s = 0x10;
        render->unk_1C &= 0xFFFBFFFF;
        (*(u16 *)((u8 *)animation + 0x98)) |= 8;
        if (system_update_flags & 2) {
            ((ActorRecord *)animation)->action_phase.u = 2;
            break;
        }
        render->unk_8A = 0x800 / ((ActorRecord *)animation)->action_timer.s;
        next_state = ((ActorRecord *)animation)->action_phase.u + 1;
        ((ActorRecord *)animation)->action_phase.u = next_state;
        break;
    case 1:
        move_frames = ((ActorRecord *)animation)->action_timer.s - 2;
        if (move_frames > 0) {
            ObjectPosition *target = view_reference_entity;

            motion->velocity_x =
                ((target->x.w.i - motion->x.w.i) << 16) / move_frames;
            motion->velocity_y =
                ((target->y.w.i - motion->y.w.i) << 16) /
                (((ActorRecord *)animation)->action_timer.s - 2);
        } else {
            ObjectPosition *target = view_reference_entity;

    /* MATCH: retain these views for production byte identity. */
            (*(s32 *)((u8 *)motion + 0x10)) = 0;
            (*(s32 *)((u8 *)motion + 0xC)) = 0;
            (*(u16 *)((u8 *)motion + 2)) = *(u16 *)&target->x.w.i;
            motion->y.unsigned_parts.integer = *(u16 *)&target->y.w.i;
        }

        frames_left = ((ActorRecord *)animation)->action_timer.s;
        if (frames_left != 0) {
            {
                s16 *target_height = &actor_hop_target_height;

                height_offset = rsin(frames_left << 6) >> 4;
                motion->velocity_z =
                    ((*target_height - height_offset - motion->z.w.i) << 16) /
                    ((ActorRecord *)animation)->action_timer.s;
            }
        }

        scale_value = scale->scale_x - render->unk_8A;
        scale->scale_x = scale_value;
        scale->scale_y = scale_value;

        frames_left = ((ActorRecord *)animation)->action_timer.u - 1;
        ((ActorRecord *)animation)->action_timer.s = frames_left;
        if (frames_left < 0) {
    /* MATCH: retain these views for production byte identity. */
            (*(s32 *)((u8 *)motion + 0x14)) = 0;
            render->unk_88 = (u16)actor_hop_target_height;
            motion->z.unsigned_parts.integer = (u16)actor_hop_target_height;
            ((ActorRecord *)animation)->unk_90.parts.high.s = 0;
            next_state = ((ActorRecord *)animation)->action_phase.u + 1;
            ((ActorRecord *)animation)->action_phase.u = next_state;
            break;
        }
        break;
    case 2:
        scale->scale_y = 0;
        scale->scale_x = 0;

        {
            s32 flags = render->unk_1C;

            flags |= 0x800000;
            render->unk_1C = flags;
        }
        break;
    }
    return 0;
}
