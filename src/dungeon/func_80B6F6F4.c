#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80172EF4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172EF4_1;   /* arg0 in func_80172EF4 */





extern void func_80047784();
extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80173D0C[];
extern s32 D_80173D24;

/* Apply directional movement, slow it down, and return the actor to its tile center. */
void func_80172EF4(void *action, void *motion, void *sprite, void *actor)
{
    s16 timer;
    s16 *x_steps;
    s16 *y_step;
    s32 direction;
    s32 initial_step_offset;
    s32 velocity_x;
    s32 velocity_y;
    s32 brake_step_offset;
    s32 biased_velocity_x;
    s32 biased_velocity_y;
    s32 target_x;
    s32 offset_x;
    s32 target_y;
    s32 offset_y;
    s32 actor_ref;
    s32 *global_state;

    direction = (((Rec_D_800E3D7C *)actor)->unk_6A.as_u16 >> 9) & 7;

    switch (((S_80172EF4_1 *)action)->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        x_steps = (s16 *)&D_8006CCD8;
        initial_step_offset = direction * 2;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 =
            *(s16 *)((u8 *)x_steps + initial_step_offset) << 0x12;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v =
            *(s16 *)((u8 *)&D_8006CCE8 + initial_step_offset) << 0x12;
        ((S_80172EF4_1 *)action)->unk_9B++;

        if (((Rec_D_800E3D7C *)actor)->unk_28 == 0) {
            goto start_action;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((S_80172EF4_1 *)action)->unk_96.s = 0;
            ((S_80172EF4_1 *)action)->unk_9B = 2;
            return;
        }

        timer = -1;
        if (((Rec_D_800E3D7C *)actor)->unk_1C.as_s32 & 0x228) {
            timer = 8;
        }
        ((S_80172EF4_1 *)action)->unk_96.s = timer;

        velocity_x = ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32;
        biased_velocity_x = velocity_x;
        if (velocity_x < 0) {
            biased_velocity_x = velocity_x + 3;
        }
        velocity_y = ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = velocity_x - (biased_velocity_x >> 2);
        biased_velocity_y = velocity_y;
        if (velocity_y < 0) {
            biased_velocity_y = velocity_y + 3;
        }
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = velocity_y - (biased_velocity_y >> 2);
        /* fall through */

    case 1:
        x_steps = (s16 *)&D_8006CCD8;
        brake_step_offset = direction * 2;
        y_step = (s16 *)((u8 *)&D_8006CCE8 + brake_step_offset);
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 -=
            *(s16 *)((u8 *)x_steps + brake_step_offset) << 0xF;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v -= *y_step << 0xF;

        if (((S_80172EF4_1 *)action)->unk_96.s > 0) {
            ((S_80172EF4_1 *)action)->unk_96.s = ((S_80172EF4_1 *)action)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((S_80172EF4_1 *)action)->unk_96.s = 0;
        }
        if (((S_80172EF4_1 *)action)->unk_96.s != 0) {
            return;
        }
        if (((Rec_D_800E3D7C *)actor)->unk_28 != 0) {
            goto increment_state;
        }

start_action:
        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800AAA54(action, motion, sprite, &D_80173D24);
        return;

increment_state:
        ((S_80172EF4_1 *)action)->unk_96.s = 4;
        ((S_80172EF4_1 *)action)->unk_9B++;
        return;

    case 2:
        if (((S_80172EF4_1 *)action)->unk_96.s != 0) {
            target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
            offset_x = ((Rec_D_800E3D7C *)motion)->unk_00.at02_s16.v - 0x20;
            ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = (target_x - offset_x) << 0x10 >> 1;
            target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
            offset_y = ((Rec_D_800E3D7C *)motion)->unk_04.at02_s16.v - 0x20;
            ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = (target_y - offset_y) << 0x10 >> 1;
        }

        timer = ((S_80172EF4_1 *)action)->unk_96.u - 1;
        ((S_80172EF4_1 *)action)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((Rec_D_800E3D7C *)motion)->unk_14.as_s32 = 0;
        ((Rec_D_800E3D7C *)motion)->unk_10.at00_s32.v = 0;
        ((Rec_D_800E3D7C *)motion)->unk_0C.as_s32 = 0;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80173D0C;
        func_80047784(sprite,
            D_80173D0C[((D_80083228 + ((Rec_D_800E3D7C *)actor)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        global_state = &D_80083460;
        actor_ref = global_state[4];
        if (actor_ref == (s32)((u8 *)actor - 0x20)) {
            global_state[4] = actor_ref & 0x7FFFFFFF;
        }
        ((S_80172EF4_1 *)action)->unk_8C = D_80170E5C;
        return;

    default:
        return;
    }
}
