#include "common.h"

typedef struct S_80173294_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; volatile s16 p; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173294_0;   /* arg0 in func_80173294 */

typedef struct S_80173294_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173294_1;   /* arg1 in func_80173294 */

typedef struct S_80173294_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x41];
    u16 unk_6A;
} S_80173294_2;   /* arg3 in func_80173294 */

typedef struct S_80173294_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173294_3;   /* arg2 in func_80173294 */



extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_801714D4;
extern u8 D_80174148;

/* Slows directional motion, then recenters the entity on its tile. */
void func_80173294(S_80173294_0 *motion_state, S_80173294_1 *motion, S_80173294_3 *tile_state, void *entity)
{
    s16 timer;
    s32 x_speed_or_entity;
    s32 velocity_z;
    s32 rounded_velocity;
    s32 state;
    s32 countdown;

    state = motion_state->unk_9B;
    if (state == 1) {
        goto slow_motion;
    }
    if ((s32)state < 2) {
        if (state == 0) {
            goto start_motion;
        }
        return;
    }
    if (state == 2) {
        goto center_on_tile;
    }
    return;

start_motion:
    func_800AD4D0(entity);
    motion->unk_0C =
        -*(s16 *)((u8 *)&D_8006CCD8 +
            ((((S_80173294_2 *)entity)->unk_6A >> 8) & 0xE)) << 15;
    motion->unk_10 =
        -*(s16 *)((u8 *)&D_8006CCE8 +
            ((((S_80173294_2 *)entity)->unk_6A >> 8) & 0xE)) << 15;
    motion_state->unk_9B++;

    if (((S_80173294_2 *)entity)->unk_28 == 0) {
        goto reset_motion;
    }
    if (tile_state->unk_14 & 0x8000) {
        motion_state->unk_96.s = 0;
        motion_state->unk_9B = 2;
        return;
    }
    timer = -1;
    if (((S_80173294_2 *)entity)->unk_1C & 0x228) {
        timer = 8;
    }
    motion_state->unk_96.s = timer;

slow_motion:
    x_speed_or_entity = motion->unk_0C;
    rounded_velocity = x_speed_or_entity;
    if (x_speed_or_entity < 0) {
        rounded_velocity = x_speed_or_entity + 3;
    }
    velocity_z = motion->unk_10;
    motion->unk_0C = x_speed_or_entity - (rounded_velocity >> 2);

    rounded_velocity = velocity_z;
    if (velocity_z < 0) {
        rounded_velocity = velocity_z + 3;
    }
    motion->unk_10 = velocity_z - (rounded_velocity >> 2);

    if (motion_state->unk_96.s > 0) {
        motion_state->unk_96.u = motion_state->unk_96.u - 1;
    } else if (tile_state->unk_14 & 0x6000) {
        motion_state->unk_96.s = 0;
    }

    if (motion_state->unk_96.s != 0) {
        return;
    }
    if (((S_80173294_2 *)entity)->unk_28 != 0) {
        goto start_centering;
    }

reset_motion:
    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800AAA54(motion_state, motion, tile_state, &D_80174148);
    return;

start_centering:
    motion_state->unk_96.s = 8;
    motion_state->unk_9B++;
    return;

center_on_tile:
    timer = motion_state->unk_96.s;
    if (timer != 0) {
        s32 tile_coord;
        s32 offset_coord;

        tile_coord = tile_state->unk_24 << 6;
        offset_coord = motion->unk_02;
        offset_coord -= 0x20;
        motion->unk_0C = ((tile_coord - offset_coord) << 15) / timer;

        offset_coord = motion->unk_06;
        offset_coord -= 0x20;
        tile_coord = tile_state->unk_25 << 6;
        motion->unk_10 =
            ((tile_coord - offset_coord) << 15) / motion_state->unk_96.s;
    }

    countdown = motion_state->unk_96.u - 1;
    motion_state->unk_96.p = countdown;
    if ((countdown << 16) > 0) {
        return;
    }

    motion->unk_14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    func_800A2B04(motion, tile_state->unk_24,
        tile_state->unk_25);
    {
        s32 *entity_slots;

        entity_slots = &D_80083460;
        x_speed_or_entity = entity_slots[4];
        if (x_speed_or_entity == (s32)((u8 *)entity - 0x20)) {
            entity_slots[4] = x_speed_or_entity & 0x7FFFFFFF;
        }
    }
    motion_state->unk_8C = &D_801714D4;
}
