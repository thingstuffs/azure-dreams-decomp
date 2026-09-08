#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80172C10_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0xB];
    u8 unk_A7;
    u8 unk_A8;
} S_80172C10_0;   /* arg0 in func_80172C10 */






extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 *D_800E3D7C;
extern u8 D_80170F20[];
extern u8 D_80173B98[];
extern u8 D_80176318[];
extern u8 D_80176378[];

/* Slows directional motion, returns the entity to its tile, and switches behavior. */
void func_80172C10(S_80172C10_0 *state, Rec_D_800E3D7C *motion, Rec_D_80082E80 *tile, void *entity)
{
    s32 mark_value;
    s32 tracked_entity;
    s32 *global_state;

    mark_value = 1;
    switch (state->unk_9B) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_0C.as_s32 =
            *(s16 *)((u8 *)&D_8006CCD8 +
                     ((((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
        motion->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 +
                     ((((Rec_D_800E3D7C *)entity)->unk_6A.as_u16 >> 8) & 0xE)) << 19;
        state->unk_9B++;

        if (((Rec_D_800E3D7C *)entity)->unk_28 == 0) {
            motion->unk_14.as_s32 = 0;
            motion->unk_10.at00_s32.v = 0;
            motion->unk_0C.as_s32 = 0;
            if (state->unk_A7 != 0) {
                func_800AAA54(state, motion, tile, D_80176378);
                if (state->unk_A8 != 0) {
                    u8 *mark_base;

                    mark_base = D_800E3D7C;
                    mark_base += state->unk_A8;
                    mark_base[0xF9] = mark_value;
                }
                return;
            }
            func_800AAA54(state, motion, tile, D_80176318);
            return;
        }

        if (tile->unk_14.at00_u16.v & 0x8000) {
            state->unk_96.s = 0;
            state->unk_9B = 2;
            return;
        }
        state->unk_96.s =
            (((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 & 0x228) ? 8 : -1;
        /* fall through */

    case 1:
        motion->unk_0C.as_s32 -= motion->unk_0C.as_s32 / 4;
        motion->unk_10.at00_s32.v -= motion->unk_10.at00_s32.v / 4;

        if (state->unk_96.s > 0) {
            state->unk_96.s = state->unk_96.u - 1;
        } else if (tile->unk_14.at00_u16.v & 0x6000) {
            state->unk_96.s = 0;
        }

        if (state->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)entity)->unk_28 != 0) {
            goto increment_state;
        }

        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        if (state->unk_A7 != 0) {
            func_800AAA54(state, motion, tile, D_80176378);
            if (state->unk_A8 != 0) {
                u8 *mark_base;

                mark_base = D_800E3D7C;
                mark_base += state->unk_A8;
                mark_base[0xF9] = 1;
            }
            return;
        }
        func_800AAA54(state, motion, tile, D_80176318);
        return;

increment_state:
        state->unk_96.s = 8;
        state->unk_9B++;
        return;

    case 2: {
        s32 x_step;
        s32 y_distance;
        s32 position_offset;
        s16 frames_left;
        u16 next_timer;

        frames_left = state->unk_96.s;
        if (frames_left > 0) {
            x_step = tile->unk_24 << 6;
            position_offset = motion->unk_00.at02_s16.v - 0x20;
            x_step = (x_step - position_offset) << 16;
            x_step = x_step / frames_left;
            position_offset = motion->unk_04.at02_s16.v - 0x20;
            motion->unk_0C.as_s32 = x_step;
            y_distance = (tile->unk_25 << 6) - position_offset;
            motion->unk_10.at00_s32.v =
                (y_distance << 16) / state->unk_96.s;
        }

        next_timer = state->unk_96.u - 1;
        state->unk_96.s = next_timer;
        if ((s32)(next_timer << 16) > 0) {
            return;
        }

        motion->unk_14.as_s32 = 0;
        motion->unk_10.at00_s32.v = 0;
        motion->unk_0C.as_s32 = 0;
        func_800A2B04(motion, tile->unk_24, tile->unk_25);

        global_state = &D_80083460;
        tracked_entity = global_state[4];
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            global_state[4] = tracked_entity & 0x7FFFFFFF;
        }
        if (state->unk_A7 != 0) {
            state->unk_8C = D_80173B98;
        } else {
            state->unk_8C = D_80170F20;
        }
        return;
    }

    default:
        return;
    }
}
