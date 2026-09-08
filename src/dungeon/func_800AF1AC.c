#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800B490C_0_pre {
    u16 unk_00;
} S_800B490C_0_pre;   /* the 0x2 bytes before arg0 in func_800B490C, addressed as arg0[-1] */

typedef struct S_800B490C_0 {
    void * unk_00;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    s16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
} S_800B490C_0;   /* arg0 in func_800B490C */

typedef struct S_800B490C_1 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_800B490C_1;   /* temp_v0 in func_800B490C */

typedef struct S_800B490C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800B490C_2;   /* arg1 in func_800B490C */

typedef struct S_800B490C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800B490C_3;   /* temp_v0_2 in func_800B490C */

typedef struct S_800B490C_4 {
    u8 pad_00[0xC];
    union { struct { u8 v; } at00; struct { s32 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
} S_800B490C_4;   /* arg2 in func_800B490C */

typedef struct S_800B490C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800B490C_5;   /* ((S_800B490C_0 *)arg0)->unk_14 in func_800B490C */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_800892E4[];
s32 func_8004491C();
extern s32 D_80044C54;
extern s32 D_800814A0[];

/* Update an attached effect with damped vertical motion, fading, shrinking, and flashing. */
void func_800B490C(void *effect, S_800B490C_2 *motion, S_800B490C_4 *sprite) {
    static void *const jt_keep[] = { &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4 };
    s32 phase;
    s16 next_phase;
    s32 rebound_speed;
    s32 velocity;
    s32 rebound_velocity;
    s32 damped_speed;
    s32 update_value;
    u16 fade_frames;
    u16 hold_frames;
    u16 shrink_frames;
    u16 frame;
    u16 scale;
    u16 next_scale;
    u8 brightness;
    u8 next_brightness;
    S_800B490C_1 *parent;
    S_800B490C_3 *parent_pos;

    parent = ((S_800B490C_0 *)effect)->unk_00;
    if (parent == NULL) {
        goto check_delay;
    }
    if (!(parent->unk_1E & 0x8000)) {
        goto check_delay;
    }
    ((S_800B490C_0 *)effect)->unk_00 = NULL;
    ((S_800B490C_0 *)effect)->unk_14 = NULL;
check_delay:
    if (((S_800B490C_0 *)effect)->unk_10 == 0) {
        goto follow_parent;
    }
    ((S_800B490C_0 *)effect)->unk_10 = (s16) ((u16) ((S_800B490C_0 *)effect)->unk_10 - 1);
    return;
follow_parent:
    parent_pos = ((S_800B490C_0 *)effect)->unk_14;
    if (parent_pos == NULL) {
        goto update_phase;
    }
    motion->unk_02 = (u16) (motion->unk_02 - (((S_800B490C_0 *)effect)->unk_18 - parent_pos->unk_02));
    ((S_800B490C_0 *)effect)->unk_18 = (u16) ((S_800B490C_5 *)(((S_800B490C_0 *)effect)->unk_14))->unk_02;
    motion->unk_06 = (u16) (motion->unk_06 - (((S_800B490C_0 *)effect)->unk_1A - ((S_800B490C_5 *)(((S_800B490C_0 *)effect)->unk_14))->unk_06));
    ((S_800B490C_0 *)effect)->unk_1A = (u16) ((S_800B490C_5 *)(((S_800B490C_0 *)effect)->unk_14))->unk_06;
    motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v - (((S_800B490C_0 *)effect)->unk_1C - ((S_800B490C_5 *)(((S_800B490C_0 *)effect)->unk_14))->unk_0A));
    ((S_800B490C_0 *)effect)->unk_1C = (u16) ((S_800B490C_5 *)(((S_800B490C_0 *)effect)->unk_14))->unk_0A;
update_phase:
    phase = ((S_800B490C_0 *)effect)->unk_08;
    if ((u32) phase >= 5U) {
        goto update_motion;
    }
    (void)jt_keep; goto *D_800892E4[(u32)(phase)];
jt_c0:
    motion->unk_14 = 0x200000;
    motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v - 0x80);
    ((S_800B490C_0 *)effect)->unk_04.at00.v = 0x200000;
    sprite->unk_1E = 0x1000U;
    sprite->unk_1C = 0x1000U;
    func_8004491C(effect - 0x20, &D_80044C54);
    ((S_800B490C_0 *)effect)->unk_0A = 0x10U;
    ((S_800B490C_0 *)effect)->unk_08 = (s16) ((u16) ((S_800B490C_0 *)effect)->unk_08 + 1);
jt_c1:
    fade_frames = ((S_800B490C_0 *)effect)->unk_0A - 1;
    ((S_800B490C_0 *)effect)->unk_0A = fade_frames;
    if ((s16) fade_frames <= 0) {
        goto advance_phase;
    }
    brightness = sprite->unk_0C.at02.v;
    next_brightness = brightness + ((s32) (0x80 - brightness) / (s16) fade_frames);
    sprite->unk_0C.at02.v = next_brightness;
    sprite->unk_0C.at01.v = next_brightness;
    sprite->unk_0C.at00.v = next_brightness;
    goto update_motion;
advance_phase:
    next_phase = (u16) ((S_800B490C_0 *)effect)->unk_08 + 1;
    goto set_phase;
jt_c3:
    hold_frames = ((S_800B490C_0 *)effect)->unk_0A - 1;
    ((S_800B490C_0 *)effect)->unk_0A = hold_frames;
    if ((hold_frames << 0x10) > 0) {
        goto update_motion;
    }
    update_value = 8;
    ((S_800B490C_0 *)effect)->unk_0A = update_value;
    next_phase = (u16) ((S_800B490C_0 *)effect)->unk_08 + 1;
set_phase:
    ((S_800B490C_0 *)effect)->unk_08 = next_phase;
    goto update_motion;
jt_c4:
    shrink_frames = ((S_800B490C_0 *)effect)->unk_0A - 1;
    ((S_800B490C_0 *)effect)->unk_0A = shrink_frames;
    if ((s16) shrink_frames <= 0) {
        goto finish_effect;
    }
    scale = sprite->unk_1E;
    next_scale = scale + ((s32) (0 - scale) / (s16) shrink_frames);
    sprite->unk_1E = next_scale;
    sprite->unk_1C = next_scale;
    motion->unk_08.at02.v = (u16) (motion->unk_08.at02.v + 6);
    goto update_motion;
finish_effect:
    ((S_800B490C_0_pre *)effect)[-1].unk_00 = (u16) (((S_800B490C_0_pre *)effect)[-1].unk_00 | 0x8000);
    D_800814A0[0] |= 0x8000;
jt_c2:
update_motion:
    motion->unk_08.at00.v = (s32) (motion->unk_08.at00.v + motion->unk_14);
    frame = ((S_800B490C_0 *)effect)->unk_0C + 1;
    ((S_800B490C_0 *)effect)->unk_0C = frame;
    if (!(frame & 1)) {
        goto update_flash;
    }
    velocity = motion->unk_14;
    update_value = velocity >> 1;
    damped_speed = velocity >> 0x11;
    if (damped_speed >= 0) {
        goto apply_damping;
    }
    damped_speed = 0 - damped_speed;
apply_damping:
    motion->unk_14 = update_value;
    if (damped_speed >= 2) {
        goto update_flash;
    }
    rebound_velocity = 0 - ((s32) ((S_800B490C_0 *)effect)->unk_04.at00.v >> 1);
    ((S_800B490C_0 *)effect)->unk_04.at00.v = rebound_velocity;
    motion->unk_14 = rebound_velocity;
    rebound_speed = ((S_800B490C_0 *)effect)->unk_04.at02.v;
    if (rebound_speed >= 0) {
        goto check_settled;
    }
    rebound_speed = 0 - rebound_speed;
check_settled:
    if (rebound_speed >= 2) {
        goto update_flash;
    }
    if (((S_800B490C_0 *)effect)->unk_08 >= 3) {
        goto update_flash;
    }
    ((S_800B490C_0 *)effect)->unk_08 = 3;
    ((S_800B490C_0 *)effect)->unk_0A = 8U;
update_flash:
    if (((S_800B490C_0 *)effect)->unk_0E == 0) {
        goto done;
    }
    update_value = 0x2CF0F0F0;
    if (!(((S_800B490C_0 *)effect)->unk_0C & 3)) {
        goto set_flash_color;
    }
    update_value = 0x2C404040;
set_flash_color:
    sprite->unk_0C.at00u.v = update_value;
done:
    return;
}
