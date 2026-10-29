#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/object_flags.h"
#include "sdk/libgte.h"
#include "dungeon/actor/effect.h"

typedef struct S_8017085C_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x4];
    u16 unk_18;
    u8 pad_1A[0x3E];
    s8 unk_58;
    s8 unk_59;
    u8 pad_5A[0x2];
    s32 unk_5C;
} S_8017085C_0;   /* arg0 in update_vertical_motion_and_effect */


typedef struct S_8017085C_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8017085C_2;   /* arg2 in update_vertical_motion_and_effect */

/* Updates vertical animation and triggers an effect upon reaching the resting height. */
void update_vertical_motion_and_effect(void *motion, ObjectPosition *position, void *effect) {
    s8 effect_args[4];
    s16 world_z;
    s16 state;
    s16 world_x;
    s32 phase;
    s32 tile_z;
    s32 height_offset;
    s32 centered_z;
    u16 frame;
    u16 frame_2;
    u16 elapsed;
    u16 old_state;

    state = ((S_8017085C_0 *)motion)->unk_12.s;
    switch (state) {
    case 0:
        frame_2 = ((S_8017085C_0 *)motion)->unk_18;
        ((S_8017085C_0 *)motion)->unk_18 = frame_2 + 1;
        phase = (s32)((u32)frame_2 << 0x10);
        phase >>= 4;
        ((S_8017085C_0 *)motion)->unk_5C = (0 - rsin(phase / 80)) << 7;
        height_offset = ((S_8017085C_0 *)motion)->unk_5C - 0x200000;
        position->z.v = position->velocity_z + height_offset;

        return;
    case 1:
        frame = ((S_8017085C_0 *)motion)->unk_18;
        ((S_8017085C_0 *)motion)->unk_18 = frame + 1;
        phase = (s32)((u32)frame << 0x10);
        phase >>= 4;
        ((S_8017085C_0 *)motion)->unk_5C = (0 - rsin(phase / 80)) << 7;
        height_offset = ((S_8017085C_0 *)motion)->unk_5C - 0x200000;
        position->z.v = position->velocity_z + height_offset;

        elapsed = ((S_8017085C_0 *)motion)->unk_18;
        ((S_8017085C_0 *)motion)->unk_18 = elapsed + 1;
        if ((s16)elapsed < 0x14) {
            return;
        }

        old_state = ((S_8017085C_0 *)motion)->unk_12.u;
        ((S_8017085C_0 *)motion)->unk_18 = 0;
        ((S_8017085C_0 *)motion)->unk_12.u = old_state + 1;
        return;
    case 2:
        position->z.v += 0x20000;
        if (position->z.v < position->velocity_z) {
            return;
        }

        position->z.v = position->velocity_z;
        effect_args[1] = 0x12;
        effect_args[0] = 1;
        effect_args[2] = 0x32;
        effect_args[3] = 0;

        world_x = position->x.w.i;
        if (world_x - 0x20 >= 0) {
            ((S_8017085C_0 *)motion)->unk_58 = (world_x - 0x20) >> 6;
        } else {
            ((S_8017085C_0 *)motion)->unk_58 = (world_x + 0x1F) >> 6;
        }

        world_z = position->y.w.i;
        centered_z = world_z - 0x20;
        if (centered_z < 0) {
            centered_z = world_z + 0x1F;
        }
        tile_z = centered_z >> 6;
        ((S_8017085C_0 *)motion)->unk_59 = tile_z;
        place_item_at_valid_floor_position(((S_8017085C_0 *)motion)->unk_58, (s8)tile_z,
            position->z.w.i, ((S_8017085C_2 *)effect)->unk_08, effect_args);

        (*(u16 *)((u8 *)motion + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
