#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/sys_flags.h"
#include "sdk/libgte.h"

typedef struct S_800AB538_0 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800AB538_0;   /* p0 in update_actor_hop_and_shrink */

typedef struct S_800AB538_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
    u16 unk_8A;
} S_800AB538_1;   /* p3 in update_actor_hop_and_shrink */

typedef struct S_800AB538_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s32 unk_14;
} S_800AB538_3;   /* p1 in update_actor_hop_and_shrink */


extern u8 view_reference_entity[];
extern s16 actor_hop_target_height;

/* Move toward the target while shrinking, then mark the animation complete. */
s32 update_actor_hop_and_shrink(void *animation, void *motion, SpriteFrameState *scale, void *render_arg)
{
    S_800AB538_1 *render = render_arg;
    s32 move_frames;
    s16 frames_left;
    s32 height_offset;
    u16 scale_value;
    s32 state;
    s32 next_state;

    state = ((S_800AB538_0 *)animation)->unk_9B;
    switch (state) {
    case 0:
        ((S_800AB538_0 *)animation)->unk_96.s = 0x10;
        render->unk_1C &= 0xFFFBFFFF;
        (*(u16 *)((u8 *)animation + 0x98)) |= 8;
        if (system_update_flags & 2) {
            ((S_800AB538_0 *)animation)->unk_9B = 2;
            break;
        }
        render->unk_8A = 0x800 / ((S_800AB538_0 *)animation)->unk_96.s;
        next_state = ((S_800AB538_0 *)animation)->unk_9B + 1;
        ((S_800AB538_0 *)animation)->unk_9B = next_state;
        break;
    case 1:
        move_frames = ((S_800AB538_0 *)animation)->unk_96.s - 2;
        if (move_frames > 0) {
            ObjectPosition *target = view_reference_entity;

            (*(s32 *)((u8 *)motion + 0xC)) =
                ((target->x.w.i - ((S_800AB538_3 *)motion)->unk_02) << 16) / move_frames;
            ((S_800AB538_3 *)motion)->unk_10 =
                ((target->y.w.i - ((S_800AB538_3 *)motion)->unk_06.s) << 16) /
                (((S_800AB538_0 *)animation)->unk_96.s - 2);
        } else {
            ObjectPosition *target = view_reference_entity;

            (*(s32 *)((u8 *)motion + 0x10)) = 0;
            (*(s32 *)((u8 *)motion + 0xC)) = 0;
            (*(u16 *)((u8 *)motion + 2)) = *(u16 *)&target->x.w.i;
            ((S_800AB538_3 *)motion)->unk_06.u = *(u16 *)&target->y.w.i;
        }

        frames_left = ((S_800AB538_0 *)animation)->unk_96.s;
        if (frames_left != 0) {
            {
                s16 *target_height = &actor_hop_target_height;

                height_offset = rsin(frames_left << 6) >> 4;
                ((S_800AB538_3 *)motion)->unk_14 =
                    ((*target_height - height_offset - ((S_800AB538_3 *)motion)->unk_0A.s) << 16) /
                    ((S_800AB538_0 *)animation)->unk_96.s;
            }
        }

        scale_value = scale->scale_x - render->unk_8A;
        scale->scale_x = scale_value;
        scale->scale_y = scale_value;

        frames_left = ((S_800AB538_0 *)animation)->unk_96.u - 1;
        ((S_800AB538_0 *)animation)->unk_96.s = frames_left;
        if (frames_left < 0) {
            (*(s32 *)((u8 *)motion + 0x14)) = 0;
            render->unk_88 = (u16)actor_hop_target_height;
            ((S_800AB538_3 *)motion)->unk_0A.u = (u16)actor_hop_target_height;
            ((S_800AB538_0 *)animation)->unk_92 = 0;
            next_state = ((S_800AB538_0 *)animation)->unk_9B + 1;
            ((S_800AB538_0 *)animation)->unk_9B = next_state;
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
