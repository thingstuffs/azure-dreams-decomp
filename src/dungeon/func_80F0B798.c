#include "common.h"

typedef struct S_80172F98_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80172F98_0;   /* arg0 in func_80172F98 */

typedef struct S_80172F98_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x41];
    u16 unk_6A;
} S_80172F98_1;   /* arg3 in func_80172F98 */

typedef struct S_80172F98_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80172F98_2;   /* arg1 in func_80172F98 */

typedef struct S_80172F98_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80172F98_3;   /* arg2 in func_80172F98 */



typedef struct {
    u8 pad00[0x10];
    s32 field10;
} D_80083460_t;

extern void func_800A2B04();
extern void func_800AAA54();
extern void func_800AD4D0();

extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern D_80083460_t D_80083460;
extern u8 D_80170F74[];
extern u8 D_80173D60[];

void func_80172F98(S_80172F98_0 *arg0, S_80172F98_2 *arg1, S_80172F98_3 *arg2, void *arg3)
{
    s16 state_2_timer;
    s16 next_timer;
    s16 initial_timer;
    s32 y_value;
    s32 direction;
    s32 x_value;
    s32 x_adjusted;
    s32 y_adjusted;
    s32 state_2_target;
    s32 state_2_origin;
    s32 state_2_target_2;
    s32 state_2_origin_2;
    u8 state;

    state = arg0->unk_9B;
    direction = (((S_80172F98_1 *)arg3)->unk_6A >> 9) & 7;

    switch (state) {
    case 0:
        goto state_0;
    case 1:
        goto state_1;
    case 2:
        goto state_2;
    default:
        goto end;
    }

state_0:
    func_800AD4D0(arg3);
    arg1->unk_0C =
        ((s16 *)&D_8006CCD8)[direction] << 16;
    arg1->unk_10 =
        ((s16 *)&D_8006CCE8)[direction] << 16;
    arg0->unk_9B++;

    if (((S_80172F98_1 *)arg3)->unk_28 == 0) {
        goto reset_and_start;
    }
    if (arg2->unk_14 & 0x8000) {
        arg0->unk_96.s = 0;
        arg0->unk_9B = 2;
        goto end;
    }

    initial_timer = -1;
    if (((S_80172F98_1 *)arg3)->unk_1C & 0x228) {
        initial_timer = 8;
    }
    arg0->unk_96.s = initial_timer;

    x_value = arg1->unk_0C;
    x_adjusted = x_value;
    if (x_value < 0) {
        x_adjusted = x_value + 3;
    }
    arg1->unk_0C = x_value - (x_adjusted >> 2);

    y_value = arg1->unk_10;
    y_adjusted = y_value;
    if (y_value < 0) {
        y_adjusted = y_value + 3;
    }
    arg1->unk_10 = y_value - (y_adjusted >> 2);

state_1:
    arg1->unk_0C -=
        ((s16 *)&D_8006CCD8)[direction] << 13;
    arg1->unk_10 -=
        ((s16 *)&D_8006CCE8)[direction] << 13;

    if (arg0->unk_96.s > 0) {
        arg0->unk_96.u = arg0->unk_96.u - 1;
        goto timer_done;
    }
    if (arg2->unk_14 & 0x6000) {
        arg0->unk_96.s = 0;
    }

timer_done:
    if (arg0->unk_96.s != 0) {
        goto end;
    }
    if (((S_80172F98_1 *)arg3)->unk_28 != 0) {
        goto continue_state;
    }

reset_and_start:
    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800AAA54(arg0, arg1, arg2, D_80173D60);
    goto end;

continue_state:
    arg0->unk_96.s = 8;
    arg0->unk_9B++;
    goto end;

state_2:
    state_2_timer = arg0->unk_96.s;
    if (state_2_timer != 0) {
        state_2_target = arg2->unk_24 << 6;
        state_2_origin = arg1->unk_02 - 0x20;
        arg1->unk_0C =
            ((state_2_target - state_2_origin) << 15) / state_2_timer;
        state_2_target_2 = arg2->unk_25 << 6;
        state_2_origin_2 = arg1->unk_06 - 0x20;
        arg1->unk_10 =
            ((state_2_target_2 - state_2_origin_2) << 15) /
            arg0->unk_96.s;
    }

    next_timer = arg0->unk_96.u - 1;
    arg0->unk_96.u = next_timer;
    if (next_timer > 0) {
        goto end;
    }

    arg1->unk_14 = 0;
    arg1->unk_10 = 0;
    arg1->unk_0C = 0;
    func_800A2B04(arg1, arg2->unk_24, arg2->unk_25);

    if (D_80083460.field10 == (s32)arg3 - 0x20) {
        D_80083460.field10 &= 0x7FFFFFFF;
    }
    arg0->unk_8C = D_80170F74;

end:
    return;
}

/* MECHANISM: The natural long-lived arguments preserve the retail 0x28 frame and s1/s0/s2/s3/s4 roles.
   Typed s16 array indexing materializes each table base before its direction shift.
   Split expression-form s32 coordinate temps block fold reassociation and schedule the second lh over the first divide result. */
