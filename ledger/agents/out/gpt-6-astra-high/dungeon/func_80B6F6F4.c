#include "common.h"

typedef struct S_80172EF4_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_80172EF4_0;   /* arg3 in func_80172EF4 */

typedef struct S_80172EF4_1 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172EF4_1;   /* arg0 in func_80172EF4 */

typedef struct S_80172EF4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172EF4_2;   /* arg1 in func_80172EF4 */

typedef struct S_80172EF4_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172EF4_3;   /* arg2 in func_80172EF4 */



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

    direction = (((S_80172EF4_0 *)actor)->unk_6A >> 9) & 7;

    switch (((S_80172EF4_1 *)action)->unk_9B) {
    case 0:
        func_800AD4D0(actor);
        x_steps = (s16 *)&D_8006CCD8;
        initial_step_offset = direction * 2;
        ((S_80172EF4_2 *)motion)->unk_0C =
            *(s16 *)((u8 *)x_steps + initial_step_offset) << 0x12;
        ((S_80172EF4_2 *)motion)->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 + initial_step_offset) << 0x12;
        ((S_80172EF4_1 *)action)->unk_9B++;

        if (((S_80172EF4_0 *)actor)->unk_28 == 0) {
            goto start_action;
        }
        if (((S_80172EF4_3 *)sprite)->unk_14 & 0x8000) {
            ((S_80172EF4_1 *)action)->unk_96.s = 0;
            ((S_80172EF4_1 *)action)->unk_9B = 2;
            return;
        }

        timer = -1;
        if (((S_80172EF4_0 *)actor)->unk_1C & 0x228) {
            timer = 8;
        }
        ((S_80172EF4_1 *)action)->unk_96.s = timer;

        velocity_x = ((S_80172EF4_2 *)motion)->unk_0C;
        biased_velocity_x = velocity_x;
        if (velocity_x < 0) {
            biased_velocity_x = velocity_x + 3;
        }
        velocity_y = ((S_80172EF4_2 *)motion)->unk_10;
        ((S_80172EF4_2 *)motion)->unk_0C = velocity_x - (biased_velocity_x >> 2);
        biased_velocity_y = velocity_y;
        if (velocity_y < 0) {
            biased_velocity_y = velocity_y + 3;
        }
        ((S_80172EF4_2 *)motion)->unk_10 = velocity_y - (biased_velocity_y >> 2);
        /* fall through */

    case 1:
        x_steps = (s16 *)&D_8006CCD8;
        brake_step_offset = direction * 2;
        y_step = (s16 *)((u8 *)&D_8006CCE8 + brake_step_offset);
        ((S_80172EF4_2 *)motion)->unk_0C -=
            *(s16 *)((u8 *)x_steps + brake_step_offset) << 0xF;
        ((S_80172EF4_2 *)motion)->unk_10 -= *y_step << 0xF;

        if (((S_80172EF4_1 *)action)->unk_96.s > 0) {
            ((S_80172EF4_1 *)action)->unk_96.s = ((S_80172EF4_1 *)action)->unk_96.u - 1;
        } else if (((S_80172EF4_3 *)sprite)->unk_14 & 0x6000) {
            ((S_80172EF4_1 *)action)->unk_96.s = 0;
        }
        if (((S_80172EF4_1 *)action)->unk_96.s != 0) {
            return;
        }
        if (((S_80172EF4_0 *)actor)->unk_28 != 0) {
            goto increment_state;
        }

start_action:
        ((S_80172EF4_2 *)motion)->unk_14 = 0;
        ((S_80172EF4_2 *)motion)->unk_10 = 0;
        ((S_80172EF4_2 *)motion)->unk_0C = 0;
        func_800AAA54(action, motion, sprite, &D_80173D24);
        return;

increment_state:
        ((S_80172EF4_1 *)action)->unk_96.s = 4;
        ((S_80172EF4_1 *)action)->unk_9B++;
        return;

    case 2:
        if (((S_80172EF4_1 *)action)->unk_96.s != 0) {
            target_x = ((S_80172EF4_3 *)sprite)->unk_24 << 6;
            offset_x = ((S_80172EF4_2 *)motion)->unk_02 - 0x20;
            ((S_80172EF4_2 *)motion)->unk_0C = (target_x - offset_x) << 0x10 >> 1;
            target_y = ((S_80172EF4_3 *)sprite)->unk_25 << 6;
            offset_y = ((S_80172EF4_2 *)motion)->unk_06 - 0x20;
            ((S_80172EF4_2 *)motion)->unk_10 = (target_y - offset_y) << 0x10 >> 1;
        }

        timer = ((S_80172EF4_1 *)action)->unk_96.u - 1;
        ((S_80172EF4_1 *)action)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((S_80172EF4_2 *)motion)->unk_14 = 0;
        ((S_80172EF4_2 *)motion)->unk_10 = 0;
        ((S_80172EF4_2 *)motion)->unk_0C = 0;
        func_800A2B04(motion, ((S_80172EF4_3 *)sprite)->unk_24, ((S_80172EF4_3 *)sprite)->unk_25);

        (*(void * *)((u8 *)sprite + 0x2C)) = D_80173D0C;
        func_80047784(sprite,
            D_80173D0C[((D_80083228 + ((S_80172EF4_0 *)actor)->unk_2A + 0x100) >> 9) & 7],
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
