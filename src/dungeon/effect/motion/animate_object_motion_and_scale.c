#include "common.h"
#include "dungeon/effect/motion.h"
#include "shared/object_flags.h"
#include "dungeon/actor/effect.h"

typedef struct S_800B80D8_0 {
    u8 pad_00[0xA2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
    u16 unk_A4;
    u8 pad_A6[0xA];
    s16 unk_B0;
    s16 unk_B2;
} S_800B80D8_0;   /* arg0 in animate_object_motion_and_scale */

typedef struct S_800B80D8_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800B80D8_1;   /* arg2 in animate_object_motion_and_scale */

extern s32 item_effect_descriptor;

/* Animate object motion and scale, then signal completion. */
void animate_object_motion_and_scale(void *object, ObjectPosition *motion, void *display)
{
    s16 state;
    s32 velocity;
    u16 frames_left;
    u16 scale;

    state = ((S_800B80D8_0 *)object)->unk_A2.s;
    switch (state) {
    case 0:
        if (((S_800B80D8_1 *)display)->unk_14 & 0x8000) {
            ((S_800B80D8_0 *)object)->unk_A2.u = 2;
            return;
        }
        ((S_800B80D8_0 *)object)->unk_A4 = 12;
        ((S_800B80D8_0 *)object)->unk_A2.u++;
    case 1:
        velocity = motion->velocity_z + 0x30000;
        motion->velocity_z = velocity;
        motion->z.v += velocity;
        scale = ((S_800B80D8_1 *)display)->unk_1C;
        if (scale < 0x1000) {
            ((S_800B80D8_1 *)display)->unk_1C = scale + 0x50;
            ((S_800B80D8_1 *)display)->unk_1E += 0x50;
        }
        frames_left = ((S_800B80D8_0 *)object)->unk_A4 - 1;
        ((S_800B80D8_0 *)object)->unk_A4 = frames_left;
        if ((frames_left << 16) != 0) {
            return;
        }
        motion->velocity_z = 0;
        ((S_800B80D8_0 *)object)->unk_A2.u++;
        return;
    case 2:
        place_item_at_valid_floor_position(((S_800B80D8_0 *)object)->unk_B0,
                      ((S_800B80D8_0 *)object)->unk_B2,
                      (s16)(((u16) motion->z.w.i) - 0x20),
                      &item_effect_descriptor,
                      (u8 *)object + 0x98);
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
}
