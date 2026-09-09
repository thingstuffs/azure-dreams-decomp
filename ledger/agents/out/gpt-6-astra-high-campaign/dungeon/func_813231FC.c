#include "common.h"


extern s32 func_800990FC(s32, u8 *, void *);
extern s32 func_80099194(u8 *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern void func_800A5720(s32);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern u8 D_80083460[];
extern u8 D_8016A808[];


typedef struct S_8016A9FC_0 {
    u8 pad_00[0x12];
    union { s16 s; u16 u; } unk_12;   /* accessed as both */
    u8 pad_14[0x6];
    u16 unk_1A;
} S_8016A9FC_0;   /* arg0 in func_8016A9FC */

typedef struct S_8016A9FC_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016A9FC_1;   /* counter_base in func_8016A9FC */

/* Handles a timed fade-out and fade-in, then marks the effect complete. */
void func_8016A9FC(void *effect) {
    s32 state;
    register s32 state_arg ASM_REG("$4");
    register s32 call_result ASM_REG("$5");
    u16 frames;
    u8 fade_green;
    u8 fade_blue;
    u8 *fade_colors;
    u8 *effect_counts;
    s32 result;
    s32 first_result;

    state = ((S_8016A9FC_0 *)effect)->unk_12.s;
    state_arg = ((S_8016A9FC_0 *)effect)->unk_12.u;
    fade_colors = D_80083160;

    if (state == 1) {
        goto wait_frames;
    }
    if (state >= 2) {
        goto check_fade_in;
    }
    if (state == 0) {
        goto fade_out;
    }
    return;

check_fade_in:
    if (state == 2) {
        goto fade_in;
    }
    return;

fade_out:
    if (fade_colors[0xA8] >= 0x65) {
        fade_colors[0xA8] -= 4;
        fade_green = fade_colors[0xA9] - 4;
        fade_blue = fade_colors[0xAA] - 4;
        goto store_fades;
    }
    ((S_8016A9FC_0 *)effect)->unk_12.u = state_arg + 1;
    ((S_8016A9FC_0 *)effect)->unk_1A = 0;
    result = func_800990FC(state_arg, fade_colors, effect);
    state_arg = 0xA;
    ASM_KEEP_NV(result);
    call_result = result;
    first_result = call_result;
    result = func_8009929C(state_arg, call_result);
    result = func_8009929C(0xA, result);
    result = func_80099194(D_8016A808, result);
    result = func_8009929C(0xA, result);
    result = func_8009929C(0xA, result);
    result = func_8009929C(0xA, result);
    result = func_8009929C(1, result);
    func_80099290(result);
    func_800A5720(first_result);
    return;

wait_frames:
    frames = ((S_8016A9FC_0 *)effect)->unk_1A;
    ((S_8016A9FC_0 *)effect)->unk_1A = frames + 1;
    if ((s16)frames < 0x3C) {
        goto finish;
    }
    ((S_8016A9FC_0 *)effect)->unk_1A = 0;
    ((S_8016A9FC_0 *)effect)->unk_12.u++;
    return;

fade_in:
    result = fade_colors[0xA8];
    ASM_KEEP_NV(result);
    if ((u32)(result & 0xFF) < 0x80) {
        fade_colors[0xA8] = result + 4;
        fade_green = fade_colors[0xA9] + 4;
        fade_blue = fade_colors[0xAA] + 4;
store_fades:
        fade_colors[0xA9] = fade_green;
        fade_colors[0xAA] = fade_blue;
        return;
    }
    fade_colors[0xAA] = 0x80;
    fade_colors[0xA9] = 0x80;
    fade_colors[0xA8] = 0x80;
    effect_counts = D_80083460;
    ((S_8016A9FC_1 *)effect_counts)->unk_0A--;
    (*(u16 *)((u8 *)effect + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;

finish:
    return;
}
