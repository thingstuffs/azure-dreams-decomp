#include "common.h"

typedef struct S_80173F0C_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 pad_0A[0xA];
    u16 unk_14;
    u8 pad_16[0x32];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_80173F0C_0;   /* arg0 in func_80173F0C */

typedef struct S_80173F0C_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_80173F0C_1;   /* arg2 in func_80173F0C */

typedef struct S_80173F0C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80173F0C_2;   /* arg1 in func_80173F0C */



typedef struct {
    u8 bytes[8];
} Unaligned8;

typedef struct {
    void *field0;
    void *field4;
    Unaligned8 field8;
    Unaligned8 field10;
    s16 field18;
    s16 field1A;
    u32 unused1C;
} CallRecord;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} OutputVector;

extern void func_800478B8(void *);
extern s32 rand(void);
extern void func_800DBA90(void *);
extern u32 D_800814A0;

/* Updates the effect's motion and fade, then marks it for removal. */
void func_80173F0C(void *effect, void *position, void *visual)
{
    CallRecord transform;
    OutputVector transformed_pos;
    s16 state;
    s32 quarter_angle;
    u16 angle;

    state = ((S_80173F0C_0 *)effect)->unk_4C.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800478B8(visual);
    if (((S_80173F0C_1 *)visual)->unk_14 & 0x6000) {
        ((S_80173F0C_1 *)visual)->unk_04 = 0;
        ((S_80173F0C_1 *)visual)->unk_05 = 0;
    }
    ((S_80173F0C_1 *)visual)->unk_0C += 0xFFE7E7E8;
    if ((u8)((S_80173F0C_1 *)visual)->unk_0C < 0x30U) {
        ((S_80173F0C_0 *)effect)->unk_4C.u++;
    }

    angle = ((S_80173F0C_0 *)effect)->unk_08 + 10;
    quarter_angle = (s32)(angle << 16) >> 18;
    ((S_80173F0C_0 *)effect)->unk_08 = angle;
    ((S_80173F0C_0 *)effect)->unk_04 = (u16)(-(quarter_angle * quarter_angle) >> 4);

    {
        s32 height_jitter;
        s32 height;

        height_jitter = rand() & 0x7F;

        height = ((S_80173F0C_0 *)effect)->unk_14;
        height += 0x140;
        height += height_jitter;
        ((S_80173F0C_0 *)effect)->unk_14 = height;
    }
    ((S_80173F0C_0 *)effect)->unk_04 += (s32)(((S_80173F0C_0 *)effect)->unk_48 << 16) >> 17;
    if (((S_80173F0C_0 *)effect)->unk_48 & 1) {
        ((S_80173F0C_0 *)effect)->unk_08++;
    }

    transform.field0 = (u8 *)effect + 4;
    transform.field4 = &transformed_pos;
    transform.field8 = *(Unaligned8 *)((u8 *)effect + 0x14);
    transform.field10 = *(Unaligned8 *)((u8 *)effect + 0xC);
    transform.field18 = 1;
    transform.field1A = 1;
    func_800DBA90(&transform);
    ((S_80173F0C_2 *)position)->unk_02 = transformed_pos.x;
    ((S_80173F0C_2 *)position)->unk_06 = transformed_pos.y;
    ((S_80173F0C_2 *)position)->unk_0A = transformed_pos.z;
    ((S_80173F0C_0 *)effect)->unk_48--;
    goto done;

state_one:
    (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
