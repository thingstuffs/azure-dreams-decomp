#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80173770_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; volatile s16 p; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173770_0;   /* arg0 in func_80173770 */






extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80171094;
extern u8 D_801764B0;

/* Slows directional motion, then aligns the entity to its tile and finishes the motion state. */
void func_80173770(S_80173770_0 *motion_state, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile, void *entity)
{
    s16 frames_left;
    s32 velocity_or_entity;
    s32 y_velocity;
    s32 division_bias;
    s32 state;
    s32 next_timer;

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
        goto align_to_tile;
    }
    return;

start_motion:
    func_800AD4D0(entity);
    motion->unk_0C.as_s32 =
        *(s16 *)((u8 *)&D_8006CCD8 +
            ((((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
    motion->unk_10.at00_s32.v =
        *(s16 *)((u8 *)&D_8006CCE8 +
            ((((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
    motion_state->unk_9B++;

    if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
        goto reset_motion;
    }
    if (tile->unk_14.at00_u16.v & 0x8000) {
        motion_state->unk_96.s = 0;
        motion_state->unk_9B = 2;
        return;
    }
    frames_left = -1;
    if (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x228) {
        frames_left = 8;
    }
    motion_state->unk_96.s = frames_left;

slow_motion:
    velocity_or_entity = motion->unk_0C.as_s32;
    division_bias = velocity_or_entity;
    if (velocity_or_entity < 0) {
        division_bias = velocity_or_entity + 3;
    }
    y_velocity = motion->unk_10.at00_s32.v;
    motion->unk_0C.as_s32 = velocity_or_entity - (division_bias >> 2);

    division_bias = y_velocity;
    if (y_velocity < 0) {
        division_bias = y_velocity + 3;
    }
    motion->unk_10.at00_s32.v = y_velocity - (division_bias >> 2);

    if (motion_state->unk_96.s > 0) {
        motion_state->unk_96.u = motion_state->unk_96.u - 1;
    } else if (tile->unk_14.at00_u16.v & 0x6000) {
        motion_state->unk_96.s = 0;
    }

    if (motion_state->unk_96.s != 0) {
        return;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
        goto start_alignment;
    }

reset_motion:
    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800AAA54(motion_state, motion, tile, &D_801764B0);
    return;

start_alignment:
    motion_state->unk_96.s = 8;
    motion_state->unk_9B++;
    return;

align_to_tile:
    frames_left = motion_state->unk_96.s;
    if (frames_left > 0) {
        s32 tile_coord;
        s32 coord_offset;

        tile_coord = tile->unk_24 << 6;
        coord_offset = motion->unk_00.at02_s16.v;
        coord_offset -= 0x20;
        motion->unk_0C.as_s32 = ((tile_coord - coord_offset) << 16) / frames_left;

        coord_offset = motion->unk_04.at02_s16.v;
        coord_offset -= 0x20;
        tile_coord = tile->unk_25 << 6;
        motion->unk_10.at00_s32.v =
            ((tile_coord - coord_offset) << 16) / motion_state->unk_96.s;
    }

    next_timer = motion_state->unk_96.u - 1;
    motion_state->unk_96.p = next_timer;
    if ((next_timer << 16) > 0) {
        return;
    }

    motion->unk_14.as_s32 = 0;
    motion->unk_10.at00_s32.v = 0;
    motion->unk_0C.as_s32 = 0;
    func_800A2B04(motion, tile->unk_24,
        tile->unk_25);
    {
        s32 *entity_globals;

        entity_globals = &D_80083460;
        velocity_or_entity = entity_globals[4];
        if (velocity_or_entity == (s32)((u8 *)entity - 0x20)) {
            entity_globals[4] = velocity_or_entity & 0x7FFFFFFF;
        }
    }
    motion_state->unk_8C = &D_80171094;
}
