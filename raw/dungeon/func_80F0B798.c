#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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

void func_80172F98(void *arg0, void *arg1, void *arg2, void *arg3)
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

    state = FIELD(arg0, u8, 0x9B);
    direction = (FIELD(arg3, u16, 0x6A) >> 9) & 7;

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
    FIELD(arg1, s32, 0x0C) =
        ((s16 *)&D_8006CCD8)[direction] << 16;
    FIELD(arg1, s32, 0x10) =
        ((s16 *)&D_8006CCE8)[direction] << 16;
    FIELD(arg0, u8, 0x9B)++;

    if (FIELD(arg3, u8, 0x28) == 0) {
        goto reset_and_start;
    }
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, s16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B) = 2;
        goto end;
    }

    initial_timer = -1;
    if (FIELD(arg3, u32, 0x1C) & 0x228) {
        initial_timer = 8;
    }
    FIELD(arg0, s16, 0x96) = initial_timer;

    x_value = FIELD(arg1, s32, 0x0C);
    x_adjusted = x_value;
    if (x_value < 0) {
        x_adjusted = x_value + 3;
    }
    FIELD(arg1, s32, 0x0C) = x_value - (x_adjusted >> 2);

    y_value = FIELD(arg1, s32, 0x10);
    y_adjusted = y_value;
    if (y_value < 0) {
        y_adjusted = y_value + 3;
    }
    FIELD(arg1, s32, 0x10) = y_value - (y_adjusted >> 2);

state_1:
    FIELD(arg1, s32, 0x0C) -=
        ((s16 *)&D_8006CCD8)[direction] << 13;
    FIELD(arg1, s32, 0x10) -=
        ((s16 *)&D_8006CCE8)[direction] << 13;

    if (FIELD(arg0, s16, 0x96) > 0) {
        FIELD(arg0, u16, 0x96) = FIELD(arg0, u16, 0x96) - 1;
        goto timer_done;
    }
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg0, s16, 0x96) = 0;
    }

timer_done:
    if (FIELD(arg0, s16, 0x96) != 0) {
        goto end;
    }
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto continue_state;
    }

reset_and_start:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800AAA54(arg0, arg1, arg2, D_80173D60);
    goto end;

continue_state:
    FIELD(arg0, s16, 0x96) = 8;
    FIELD(arg0, u8, 0x9B)++;
    goto end;

state_2:
    state_2_timer = FIELD(arg0, s16, 0x96);
    if (state_2_timer != 0) {
        state_2_target = FIELD(arg2, u8, 0x24) << 6;
        state_2_origin = FIELD(arg1, s16, 2) - 0x20;
        FIELD(arg1, s32, 0x0C) =
            ((state_2_target - state_2_origin) << 15) / state_2_timer;
        state_2_target_2 = FIELD(arg2, u8, 0x25) << 6;
        state_2_origin_2 = FIELD(arg1, s16, 6) - 0x20;
        FIELD(arg1, s32, 0x10) =
            ((state_2_target_2 - state_2_origin_2) << 15) /
            FIELD(arg0, s16, 0x96);
    }

    next_timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = next_timer;
    if (next_timer > 0) {
        goto end;
    }

    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));

    if (D_80083460.field10 == (s32)arg3 - 0x20) {
        D_80083460.field10 &= 0x7FFFFFFF;
    }
    FIELD(arg0, void *, 0x8C) = D_80170F74;

end:
    return;
}

/* MECHANISM: The natural long-lived arguments preserve the retail 0x28 frame and s1/s0/s2/s3/s4 roles.
   Typed s16 array indexing materializes each table base before its direction shift.
   Split expression-form s32 coordinate temps block fold reassociation and schedule the second lh over the first divide result. */
