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

void func_80173F0C(void *arg0, void *arg1, void *arg2)
{
    CallRecord record;
    OutputVector output;
    s16 state;
    s32 value;
    u16 angle;

    state = ((S_80173F0C_0 *)arg0)->unk_4C.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800478B8(arg2);
    if (((S_80173F0C_1 *)arg2)->unk_14 & 0x6000) {
        ((S_80173F0C_1 *)arg2)->unk_04 = 0;
        ((S_80173F0C_1 *)arg2)->unk_05 = 0;
    }
    ((S_80173F0C_1 *)arg2)->unk_0C += 0xFFE7E7E8;
    if ((u8)((S_80173F0C_1 *)arg2)->unk_0C < 0x30U) {
        ((S_80173F0C_0 *)arg0)->unk_4C.u++;
    }

    angle = ((S_80173F0C_0 *)arg0)->unk_08 + 10;
    value = (s32)(angle << 16) >> 18;
    ((S_80173F0C_0 *)arg0)->unk_08 = angle;
    ((S_80173F0C_0 *)arg0)->unk_04 = (u16)(-(value * value) >> 4);

    {
        s32 random;
        s32 height;

        random = rand() & 0x7F;
        
        height = ((S_80173F0C_0 *)arg0)->unk_14;
        height += 0x140;
        height += random;
        ((S_80173F0C_0 *)arg0)->unk_14 = height;
    }
    ((S_80173F0C_0 *)arg0)->unk_04 += (s32)(((S_80173F0C_0 *)arg0)->unk_48 << 16) >> 17;
    if (((S_80173F0C_0 *)arg0)->unk_48 & 1) {
        ((S_80173F0C_0 *)arg0)->unk_08++;
    }

    record.field0 = (u8 *)arg0 + 4;
    record.field4 = &output;
    record.field8 = *(Unaligned8 *)((u8 *)arg0 + 0x14);
    record.field10 = *(Unaligned8 *)((u8 *)arg0 + 0xC);
    record.field18 = 1;
    record.field1A = 1;
    func_800DBA90(&record);
    ((S_80173F0C_2 *)arg1)->unk_02 = output.x;
    ((S_80173F0C_2 *)arg1)->unk_06 = output.y;
    ((S_80173F0C_2 *)arg1)->unk_0A = output.z;
    ((S_80173F0C_0 *)arg0)->unk_48--;
    goto done;

state_one:
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: Declaration order puts the address-taken call record at sp+0x10 and output at sp+0x30,
   producing the 0x48 frame and exact s0/s1/s2 saves; true-space gotos preserve the tail CFG.
   A guarded v0 random-result pin plus in-place height += random closes the final addiu motion. */
