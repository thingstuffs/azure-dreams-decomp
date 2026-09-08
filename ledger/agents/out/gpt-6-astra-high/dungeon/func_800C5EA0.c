#include "common.h"


typedef struct {
    u16 unk0;
    u16 flags;
    u8 pad4[6];
    u16 fieldA;
    void *fieldC;
    void *field10;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 D_8008346C;
extern s32 D_800814A0[3];

void func_8009A028(void *arg0);


typedef struct S_800CB600_0_pre {
    u16 unk_00;
} S_800CB600_0_pre;   /* the 0x2 bytes before arg0 in func_800CB600, addressed as arg0[-1] */

typedef struct S_800CB600_0 {
    u8 pad_00[0x8A];
    union { u16 u; s16 s; } unk_8A;   /* accessed as both */
    u8 pad_8C[0x6];
    u16 unk_92;
    union { u16 u; s16 s; } unk_94;   /* accessed as both */
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u16 unk_98;
    u8 unk_9A;
    u8 pad_9B[0x2];
    u8 unk_9D;
} S_800CB600_0;   /* arg0 in func_800CB600 */

typedef struct S_800CB600_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} S_800CB600_1;   /* arg2 in func_800CB600 */

typedef struct S_800CB600_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800CB600_2;   /* arg1 in func_800CB600 */

typedef struct S_800CB600_3 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_800CB600_3;   /* temp_a0 in func_800CB600 */

/* Updates a pulsing effect through growth, activation, and shrinkage before marking it for removal. */
void func_800CB600(void *effect, S_800CB600_2 *position, S_800CB600_1 *appearance) {
    u16 next_brightness;
    u16 height_offset;
    u16 frames_left;
    s8 brightness;
    s32 pulse_boost;
    s32 phase;
    s16 grow_frames;
    s16 shrink_frames;
    s16 scale_step;
    u16 old_scale;
    u16 grown_scale;
    u16 shrunk_scale;
    S_800CB600_3 *owner;
    D_80083460_t *state;

    next_brightness = ((S_800CB600_0 *)effect)->unk_94.u + 1;
    ((S_800CB600_0 *)effect)->unk_94.u = next_brightness;
    if ((s16)next_brightness >= 0x41) {
        ((S_800CB600_0 *)effect)->unk_94.u = 0x40;
    }

    pulse_boost = ((S_800CB600_0 *)effect)->unk_94.s * 2;
    pulse_boost *= ((S_800CB600_0 *)effect)->unk_9D & 1;
    brightness = (u8)((S_800CB600_0 *)effect)->unk_94.u + pulse_boost;
    appearance->unk_0C = brightness;
    appearance->unk_0E = brightness;
    appearance->unk_0D = brightness;

    phase = ((S_800CB600_0 *)effect)->unk_9A;
    ((S_800CB600_0 *)effect)->unk_9D = ((S_800CB600_0 *)effect)->unk_9D + 1;
    if (phase == 0) {
        height_offset = ((S_800CB600_0 *)effect)->unk_8A.u - 8;
        ((S_800CB600_0 *)effect)->unk_8A.u = height_offset;
        if ((s16)height_offset < -0x80) {
            ((S_800CB600_0 *)effect)->unk_8A.s = -0x80;
        }

        position->unk_0A =
            (s16)(((S_800CB600_0 *)effect)->unk_92 + ((S_800CB600_0 *)effect)->unk_8A.u);

        old_scale = appearance->unk_1C;
        grow_frames = ((S_800CB600_0 *)effect)->unk_96.s;
        grown_scale = old_scale + ((0x1000 - old_scale) / grow_frames);
        appearance->unk_1C = grown_scale;
        appearance->unk_1E = grown_scale;

        frames_left = ((S_800CB600_0 *)effect)->unk_96.u - 1;
        ((S_800CB600_0 *)effect)->unk_96.u = frames_left;
        if ((s16)frames_left > 0) {
            return;
        }

        state = &D_80083460;
        ((S_800CB600_0 *)effect)->unk_96.u = 0;
        if (state->fieldC != 0) {
            return;
        }
        if (state->field10 != 0) {
            return;
        }
        if (state->flags & 8) {
            return;
        }

        state->fieldC = effect;
        ((S_800CB600_0 *)effect)->unk_98 |= 0x80;
        ((S_800CB600_0 *)effect)->unk_9A++;
        return;
    }

    if (phase == 1) {
        if (D_8008346C != 0) {
            return;
        }

        func_8009A028(effect);
        owner = (u8 *)effect - 0x20;
        owner->unk_10 |= 0x80000000;
        ((S_800CB600_0 *)effect)->unk_96.u = 0x10;
        ((S_800CB600_0 *)effect)->unk_9A++;
        return;
    }

    shrunk_scale = appearance->unk_1C;
    shrink_frames = ((S_800CB600_0 *)effect)->unk_96.s;
    scale_step = shrunk_scale / shrink_frames;
    shrunk_scale -= scale_step;
    appearance->unk_1C = shrunk_scale;
    appearance->unk_1E = shrunk_scale;

    frames_left = ((S_800CB600_0 *)effect)->unk_96.u - 1;
    ((S_800CB600_0 *)effect)->unk_96.u = frames_left;
    if ((s16)frames_left > 0) {
        return;
    }

    D_80083460.fieldA--;
    ((S_800CB600_0_pre *)effect)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
