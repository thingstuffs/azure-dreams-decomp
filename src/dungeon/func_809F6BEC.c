#include "common.h"

typedef struct S_801743EC_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    u8 pad_06[0x2];
    u16 unk_08;
    u8 pad_0A[0x42];
    union { s16 s; u16 u; } unk_4C;   /* accessed as both */
} S_801743EC_0;   /* arg0 in func_801743EC */

typedef struct S_801743EC_1 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x6];
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
} S_801743EC_1;   /* arg2 in func_801743EC */

typedef struct S_801743EC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801743EC_2;   /* arg1 in func_801743EC */



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
extern void func_800DBA90(void *);
extern u32 D_800814A0;

void func_801743EC(void *arg0, void *arg1, void *arg2)
{
    CallRecord record;
    OutputVector output;
    s16 state;
    s32 value;
    u16 angle;

    state = ((S_801743EC_0 *)arg0)->unk_4C.s;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800478B8(arg2);
    if (((S_801743EC_1 *)arg2)->unk_14 & 0x6000) {
        ((S_801743EC_1 *)arg2)->unk_04 = 0;
        ((S_801743EC_1 *)arg2)->unk_05 = 0;
    }
    ((S_801743EC_1 *)arg2)->unk_0C += 0xFFE7E7E8;
    if ((u8)((S_801743EC_1 *)arg2)->unk_0C < 0x30U) {
        ((S_801743EC_0 *)arg0)->unk_4C.u++;
    }

    angle = ((S_801743EC_0 *)arg0)->unk_08 + 10;
    value = (s32)(angle << 16) >> 18;
    ((S_801743EC_0 *)arg0)->unk_08 = angle;
    ((S_801743EC_0 *)arg0)->unk_04 = (u16)(-(value * value) >> 4);

    record.field0 = (u8 *)arg0 + 4;
    record.field4 = &output;
    record.field8 = *(Unaligned8 *)((u8 *)arg0 + 0x14);
    record.field10 = *(Unaligned8 *)((u8 *)arg0 + 0xC);
    record.field18 = 1;
    record.field1A = 1;
    func_800DBA90(&record);
    ((S_801743EC_2 *)arg1)->unk_02 = output.x;
    ((S_801743EC_2 *)arg1)->unk_06 = output.y;
    ((S_801743EC_2 *)arg1)->unk_0A = output.z;
    goto done;

state_one:
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: Separate 32-byte call record and 8-byte output locals establish the 0x48 frame.
   Three long-lived arguments naturally occupy s1/s2/s0; true-space gotos recover both joins.
   Two 8-byte byte-array assignments encode retail's paired unaligned aggregate copies. */
