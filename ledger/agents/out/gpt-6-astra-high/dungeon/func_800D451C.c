#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_800D9C7C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800D9C7C_1;   /* arg0 in func_800D9C7C */


typedef struct S_800D9C7C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D9C7C_3;   /* arg2 in func_800D9C7C */


extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_800D8C64[];
extern u8 D_8017586C[];
extern u8 D_8017588C[];


/* Update directional motion, then settle the position onto its tile. */
void func_800D9C7C(S_800D9C7C_1 *motion, Rec_D_800E3D7C *position, S_800D9C7C_3 *tile, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_entity;
    s32 *global_state;

    direction = (((Rec_D_800E3D7C *)source)->unk_6A.u >> 9) & 7;
    switch (motion->unk_9B) {
    case 0:
        func_800AD4D0(source);
        position->unk_0C.n =
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 18;
        position->unk_10.at00.v =
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 18;
        motion->unk_9B++;

        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            position->unk_14.s32 = 0;
            position->unk_10.at00.v = 0;
            position->unk_0C.n = 0;
            func_800AAA54(motion, position, tile, 0);
            return;
        }
        if (tile->unk_14 & 0x8000) {
            motion->unk_96.s = 0;
            motion->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_1C.s & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        motion->unk_96.s = timer;
        position->unk_0C.n -= position->unk_0C.n / 4;
        position->unk_10.at00.v -= position->unk_10.at00.v / 4;
        /* fall through */

    case 1:
        position->unk_0C.n -=
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 14;
        position->unk_10.at00.v -=
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 14;
        if (motion->unk_96.s > 0) {
            motion->unk_96.s = motion->unk_96.u - 1;
        } else if (tile->unk_14 & 0x6000) {
            motion->unk_96.s = 0;
        }
        if (motion->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_28 != 0) {
            goto increment_state;
        }
        position->unk_14.s32 = 0;
        position->unk_10.at00.v = 0;
        position->unk_0C.n = 0;
        func_800AAA54(motion, position, tile, 0);
        return;

increment_state:
        motion->unk_96.s = 8;
        motion->unk_9B++;
        return;

    case 2:
        if (motion->unk_96.s != 0) {
            {
                s32 target_x = tile->unk_24 << 6;
                s32 current_x = position->unk_00.at02.v - 0x20;

                position->unk_0C.n = ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y = tile->unk_25 << 6;
                s32 current_y = position->unk_04.at02.v - 0x20;

                position->unk_10.at00.v = ((target_y - current_y) << 15) >> 1;
            }
        }
        timer = motion->unk_96.u - 1;
        motion->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        position->unk_14.s32 = 0;
        position->unk_10.at00.v = 0;
        position->unk_0C.n = 0;
        func_800A2B04(position, tile->unk_24, tile->unk_25);

        global_state = &D_80083460;
        tracked_entity = global_state[4];
        if (tracked_entity == (s32)((u8 *)source - 0x20)) {
            global_state[4] = tracked_entity & 0x7FFFFFFF;
        }
        motion->unk_8C = D_800D8C64;
        return;

    default:
        return;
    }
}
