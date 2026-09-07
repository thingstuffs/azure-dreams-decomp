#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_8017314C_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017314C_1;   /* arg0 in func_8017314C */


typedef struct S_8017314C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_8017314C_3;   /* arg2 in func_8017314C */



extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s32 D_80083460;
extern u8 D_80170E7C;
extern u8 D_80174D5C;

/* Advance directional movement and settle the entity at its destination tile. */
void func_8017314C(S_8017314C_1 *motion_state, Rec_D_800E3D7C *entity, S_8017314C_3 *destination, void *source)
{
    s16 timer;
    s32 direction;
    s32 tracked_addr;
    s32 *global_state;

    direction = (((Rec_D_800E3D7C *)source)->unk_6A.u >> 9) & 7;
    switch (motion_state->unk_9B) {
    case 0:
        func_800AD4D0(source);
        entity->unk_0C.n =
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 19;
        entity->unk_10.at00.v =
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 19;
        motion_state->unk_9B++;

        if (((Rec_D_800E3D7C *)source)->unk_28 == 0) {
            goto start_action;
        }
        if (destination->unk_14 & 0x8000) {
            motion_state->unk_96.s = 0;
            motion_state->unk_9B = 2;
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_1C.s & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        motion_state->unk_96.s = timer;
        entity->unk_0C.n -= entity->unk_0C.n / 4;
        entity->unk_10.at00.v -= entity->unk_10.at00.v / 4;
        /* fall through */

    case 1:
        entity->unk_0C.n -=
            *(s16 *)((u8 *)&D_8006CCD8 + (direction * 2)) << 14;
        entity->unk_10.at00.v -=
            *(s16 *)((u8 *)&D_8006CCE8 + (direction * 2)) << 14;
        if (motion_state->unk_96.s > 0) {
            motion_state->unk_96.s = motion_state->unk_96.u - 1;
        } else if (destination->unk_14 & 0x6000) {
            motion_state->unk_96.s = 0;
        }
        if (motion_state->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)source)->unk_28 != 0) {
            goto increment_state;
        }
        goto start_action;

start_action:
        entity->unk_14.s32 = 0;
        entity->unk_10.at00.v = 0;
        entity->unk_0C.n = 0;
        func_800AAA54(motion_state, entity, destination, &D_80174D5C);
        return;

increment_state:
        motion_state->unk_96.s = 8;
        motion_state->unk_9B++;
        return;

    case 2:
        if (motion_state->unk_96.s != 0) {
            {
                s32 target_x;
                s32 current_x;

                target_x = destination->unk_24 << 6;
                current_x = entity->unk_00.at02.v - 0x20;
                entity->unk_0C.n =
                    ((target_x - current_x) << 15) >> 1;
            }
            {
                s32 target_y;
                s32 current_y;

                target_y = destination->unk_25 << 6;
                current_y = entity->unk_04.at02.v - 0x20;
                entity->unk_10.at00.v =
                    ((target_y - current_y) << 15) >> 1;
            }
        }
        timer = motion_state->unk_96.u - 1;
        motion_state->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
        entity->unk_14.s32 = 0;
        entity->unk_10.at00.v = 0;
        entity->unk_0C.n = 0;
        func_800A2B04(entity, destination->unk_24, destination->unk_25);

        global_state = &D_80083460;
        tracked_addr = global_state[4];
        if (tracked_addr == (s32)((u8 *)source - 0x20)) {
            global_state[4] = tracked_addr & 0x7FFFFFFF;
        }
        motion_state->unk_8C = &D_80170E7C;
        return;

    default:
        return;
    }
}
