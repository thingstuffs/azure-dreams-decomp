#include "common.h"

typedef struct S_818F9E48_0 {
    union { s16 s; u16 u; } unk_00;   /* accessed as both */
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x28];
    void * unk_2C;
    void * unk_30;
    u8 pad_34[0x64];
    u16 unk_98;
    u16 unk_9A;
} S_818F9E48_0;   /* arg0 in func_818F9E48 */

typedef struct S_818F9E48_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818F9E48_1;   /* effect in func_818F9E48 */

typedef struct S_818F9E48_2_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_818F9E48_2_pre;   /* the 0x18 bytes before owner in func_818F9E48, addressed as owner[-1] */

typedef struct S_818F9E48_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818F9E48_3;   /* out in func_818F9E48 */

typedef struct S_818F9E48_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_818F9E48_4;   /* copy in func_818F9E48 */

typedef struct S_818F9E48_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_818F9E48_5;   /* motion in func_818F9E48 */

typedef struct S_818F9E48_6 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} S_818F9E48_6;   /* ((S_818F9E48_0 *)arg0)->unk_30 in func_818F9E48 */



typedef struct PackedVector {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct Pair16 {
    s16 x;
    s16 y;
} Pair16;

typedef struct EffectState {
    u8 pad[0x38];
    u8 levels[0x60];
} EffectState;

extern PackedVector D_8002400C;
extern s16 D_800266BC;
extern s32 D_800814A0;

extern void func_80024CD4();
extern void func_80025714() __attribute__((noreturn));
extern void func_80025758() __attribute__((noreturn));
extern void func_80025908() __attribute__((noreturn));

/* Update a timed visual effect using its owner's appearance and position. */
void func_818F9E48(void *state, void *position_out, void *effect_arg) {
    s32 fade_or_phase;
    PackedVector origin;
    Pair16 anchor;
    s32 level_index;
    u8 intensity;
    s16 frame_or_phase;
    u16 effect_flags;
    void *owner;
    void *motion;
    void *owner_position;
    u16 saved_scale_x;
    u16 saved_scale_y;
    s32 one;

    origin = D_8002400C;
    D_800266BC = 1;
    ((S_818F9E48_0 *)state)->unk_98 += 0xC8;

    if (((S_818F9E48_0 *)state)->unk_02.s < 0x32) {
        level_index = 0;
        do {
            ((EffectState *)state)->levels[level_index]++;
            level_index++;
        } while (level_index < 0x60);
        func_80025714();
        return;
    }

    level_index = 0;
    do {
        intensity = ((EffectState *)state)->levels[level_index];
        if (intensity != 0) {
            ((EffectState *)state)->levels[level_index] = intensity - 1;
        }
        level_index++;
    } while (level_index < 0x60);

    frame_or_phase = ((S_818F9E48_0 *)state)->unk_02.s;
    if (frame_or_phase < 0x15) {
        fade_or_phase = (frame_or_phase * 6) - 0x79;
        ASM_TAILSLOT_PIN(fade_or_phase);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        func_80025758();
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    if (frame_or_phase >= 0x50) {
        intensity = ((0x64 - frame_or_phase) * 6) - 0x80;
        ((S_818F9E48_1 *)effect_arg)->unk_0E = intensity;
        ((S_818F9E48_1 *)effect_arg)->unk_0D = intensity;
        ((S_818F9E48_1 *)effect_arg)->unk_0C = intensity;
    }

    ((S_818F9E48_0 *)state)->unk_9A += 4;
    owner = ((S_818F9E48_0 *)state)->unk_2C;
    owner_position = ((S_818F9E48_2_pre *)owner)[-1].unk_00;
    motion = ((S_818F9E48_2_pre *)owner)[-1].unk_04;
    ((S_818F9E48_3 *)position_out)->unk_00 = ((S_818F9E48_4 *)owner_position)->unk_00;
    ((S_818F9E48_3 *)position_out)->unk_04 = ((S_818F9E48_4 *)owner_position)->unk_04;
    ((S_818F9E48_3 *)position_out)->unk_08 = ((S_818F9E48_4 *)owner_position)->unk_08;

    frame_or_phase = ((S_818F9E48_0 *)state)->unk_00.s;
    if (frame_or_phase == 0) {
        goto state_zero;
    }
    fade_or_phase = 1;
    if (frame_or_phase == fade_or_phase) {
        goto state_done;
    }
    func_80025908();
    return;

state_zero:
    ((S_818F9E48_0 *)state)->unk_00.u++;
    effect_flags = ((S_818F9E48_1 *)effect_arg)->unk_14 & 0xFF7F;
    ((S_818F9E48_1 *)effect_arg)->unk_14 = effect_flags;
    ((S_818F9E48_1 *)effect_arg)->unk_14 = effect_flags | (((S_818F9E48_5 *)motion)->unk_14 & 0xC);
    ((S_818F9E48_1 *)effect_arg)->unk_10 = ((S_818F9E48_5 *)motion)->unk_10;
    ((S_818F9E48_1 *)effect_arg)->unk_0C = ((S_818F9E48_5 *)motion)->unk_0C;
    ((S_818F9E48_1 *)effect_arg)->unk_0D = ((S_818F9E48_5 *)motion)->unk_0D;
    ((S_818F9E48_1 *)effect_arg)->unk_0E = ((S_818F9E48_5 *)motion)->unk_0E;
    ((S_818F9E48_5 *)motion)->unk_14 |= 0x80;

state_done:
    one = 1;
    anchor.x = origin.x + ((s16)origin.z >> 1);
    anchor.y = origin.y + 0x48;
    saved_scale_x = ((S_818F9E48_5 *)motion)->unk_1C;
    saved_scale_y = ((S_818F9E48_5 *)motion)->unk_1E;
    ((S_818F9E48_1 *)effect_arg)->unk_1C = saved_scale_x;
    ((S_818F9E48_1 *)effect_arg)->unk_1E = ((S_818F9E48_5 *)motion)->unk_1E;
    ((S_818F9E48_5 *)motion)->unk_1E = 0x1000;
    ((S_818F9E48_5 *)motion)->unk_1C = 0x1000;
    func_80024CD4(state, ((S_818F9E48_0 *)state)->unk_2C, &origin, &anchor, one, one);
    ((S_818F9E48_5 *)motion)->unk_1C = saved_scale_x;
    ((S_818F9E48_5 *)motion)->unk_1E = saved_scale_y;

    frame_or_phase = ((S_818F9E48_0 *)state)->unk_02.u + 1;
    ((S_818F9E48_0 *)state)->unk_02.u = frame_or_phase;
    if (frame_or_phase >= 0x65) {
        ((S_818F9E48_0 *)state)->unk_02.u = 0;
        ((S_818F9E48_0 *)state)->unk_00.u++;
        ((S_818F9E48_5 *)motion)->unk_14 &= 0xFF7F;
        ((S_818F9E48_6 *)(((S_818F9E48_0 *)state)->unk_30))->unk_9C = one;
        (*(u16 *)((u8 *)state + -2)) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* MECHANISM: Separate packed source/derived locals preserve the 0x40 frame and retail slots.
   Guarded $t0/$a3 holds plus EffectState::levels recover the prologue and base-first loop adds.
   Zero-arg noreturn tails, a $v0 tail-slot pin, ordered CFG labels, and seam fences close the ABI. */
