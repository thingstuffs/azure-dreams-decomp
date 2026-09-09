#include "common.h"

typedef struct S_80170CEC_0 {
    u8 pad_00[0x2C];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    union { u16 s; s16 u; } unk_36;   /* accessed as both */
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
} S_80170CEC_0;   /* arg0 in func_80170CEC */

typedef struct S_80170CEC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80170CEC_1;   /* entity_base in func_80170CEC */

typedef struct S_80170CEC_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x14];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_80170CEC_2;   /* record in func_80170CEC */

typedef struct S_80170CEC_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80170CEC_3;   /* arg2 in func_80170CEC */

typedef struct S_80170CEC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x82];
    u8 unk_9A;
    u8 pad_9B[0x1A];
    u8 unk_B5;
} S_80170CEC_4;   /* entity_saved in func_80170CEC */

typedef struct S_80170CEC_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170CEC_5;   /* entity in func_80170CEC */

typedef struct S_80170CEC_6 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80170CEC_6;   /* arg1 in func_80170CEC */

typedef struct S_80170CEC_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80170CEC_7;   /* copy_source in func_80170CEC */


#define VFIELD(ptr, type, off) (*(type volatile *)((u8 *)(ptr) + (off)))

extern s32 func_80042900();
extern s32 D_800814A0;
extern u8 D_800E23F8[];
extern u8 D_800E2408[];
extern u8 *D_800E3D7C[3];

/* Update the effect rotation, position, and fade, marking it finished when needed. */
void func_80170CEC(void *effect, void *position, void *visual) {
    void *entity;
    void *entity_saved;
    void *source_position;
    void *entity_base;
    void *record;
    u16 old_angle;
    u16 new_angle;
    u16 record_angle;
    s16 state;
    u16 state_bits;
    void *kind;

    entity = ((S_80170CEC_0 *)effect)->unk_40;
    source_position = VFIELD(effect, void *, 0x44);
    old_angle = VFIELD(visual, u16, 0x1A);
    entity_base = (u8 *)entity - 0x20;
    record = ((S_80170CEC_1 *)entity_base)->unk_0C;
    record_angle = ((S_80170CEC_2 *)record)->unk_06;
    new_angle = old_angle + 0x190;
       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    entity_saved = entity;
    ((S_80170CEC_3 *)visual)->unk_1A = new_angle;
    ((S_80170CEC_3 *)visual)->unk_06 = record_angle;
    if (new_angle >= 0x1001) {
        ((S_80170CEC_3 *)visual)->unk_1A = old_angle - 0xE70;
    }

    state = ((S_80170CEC_0 *)effect)->unk_2C.s;
    state_bits = ((S_80170CEC_0 *)effect)->unk_2C.u;
    if (state == 1) {
        goto track_entity;
    }
    if (state < 2) {
        if (state == 0) {
            goto fade_in;
        }
        goto do_call;
    }
    if (state == 2) {
        goto fade_out;
    }
    if (state == 3) {
        goto detach_entity;
    }
    goto do_call;

fade_in:
{
    u16 fade_step;
    s32 intensity;

    fade_step = ((S_80170CEC_0 *)effect)->unk_36.s + 1;
    intensity = ((s32)(s16)fade_step << 7) / ((S_80170CEC_0 *)effect)->unk_38;
    ((S_80170CEC_0 *)effect)->unk_36.s = fade_step;
    ((S_80170CEC_3 *)visual)->unk_0C = intensity;
    ((S_80170CEC_3 *)visual)->unk_0D = intensity;
    ((S_80170CEC_3 *)visual)->unk_0E = intensity;
    if (((S_80170CEC_0 *)effect)->unk_36.u < 5) {
        goto do_call;
    }
    ((S_80170CEC_0 *)effect)->unk_2C.u++;
    goto do_call;
}

track_entity:
    if ((((S_80170CEC_4 *)entity_saved)->unk_9A == 0x19) ||
        (((S_80170CEC_4 *)entity_saved)->unk_B5 == 0)) {
        ((S_80170CEC_0 *)effect)->unk_2C.u = state_bits + 1;
        ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
        ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
    }
    if (((S_80170CEC_5 *)entity)->unk_9A == 1) {
        ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
        ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
        ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
    }
    if ((((S_80170CEC_4 *)entity_saved)->unk_14 & 0x100000) &&
        (D_800E3D7C[0][0x9A] != 0x28)) {
        ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
        ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
        ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
    }
    if (((S_80170CEC_1 *)entity_base)->unk_1E & 0x8000) {
        ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
        ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
        ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
    }
    kind = ((S_80170CEC_2 *)record)->unk_2C;
    if ((kind == D_800E23F8) || (kind == D_800E2408)) {
        ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
        ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
        ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
    }
    ((S_80170CEC_6 *)position)->unk_00 = ((S_80170CEC_7 *)source_position)->unk_00;
    ((S_80170CEC_6 *)position)->unk_04 = ((S_80170CEC_7 *)source_position)->unk_04;
    ((S_80170CEC_6 *)position)->unk_08 = ((S_80170CEC_7 *)source_position)->unk_08;
    goto call_tail;

detach_entity:
    ((S_80170CEC_6 *)position)->unk_00 = ((S_80170CEC_7 *)source_position)->unk_00;
    ((S_80170CEC_6 *)position)->unk_04 = ((S_80170CEC_7 *)source_position)->unk_04;
    ((S_80170CEC_6 *)position)->unk_08 = ((S_80170CEC_7 *)source_position)->unk_08;
    ((S_80170CEC_3 *)visual)->unk_1C = ((S_80170CEC_2 *)record)->unk_1C;
    ((S_80170CEC_3 *)visual)->unk_1E = ((S_80170CEC_2 *)record)->unk_1E;

fade_out:
{
    u16 fade_step;
    s32 intensity;

    fade_step = ((S_80170CEC_0 *)effect)->unk_36.s - 1;
    intensity = ((s32)(s16)fade_step << 7) / ((S_80170CEC_0 *)effect)->unk_38;
    ((S_80170CEC_0 *)effect)->unk_36.s = fade_step;
    ((S_80170CEC_3 *)visual)->unk_0C = intensity;
    ((S_80170CEC_3 *)visual)->unk_0D = intensity;
    ((S_80170CEC_3 *)visual)->unk_0E = intensity;
    if (((S_80170CEC_0 *)effect)->unk_36.u <= 0) {
        goto set_flags;
    }
}

call_tail:
do_call:
    if ((func_80042900(entity_saved, 0xA) << 16) == 0) {
        return;
    }

set_flags:
    (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
}
