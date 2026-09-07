#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

    state = FIELD(arg0, s16, 0x4C);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    goto done;

state_zero:
    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, s8, 4) = 0;
        FIELD(arg2, s8, 5) = 0;
    }
    FIELD(arg2, s32, 0xC) += 0xFFE7E7E8;
    if ((u8)FIELD(arg2, s32, 0xC) < 0x30U) {
        FIELD(arg0, u16, 0x4C)++;
    }

    angle = FIELD(arg0, u16, 8) + 10;
    value = (s32)(angle << 16) >> 18;
    FIELD(arg0, u16, 8) = angle;
    FIELD(arg0, u16, 4) = (u16)(-(value * value) >> 4);

    record.field0 = (u8 *)arg0 + 4;
    record.field4 = &output;
    record.field8 = *(Unaligned8 *)((u8 *)arg0 + 0x14);
    record.field10 = *(Unaligned8 *)((u8 *)arg0 + 0xC);
    record.field18 = 1;
    record.field1A = 1;
    func_800DBA90(&record);
    FIELD(arg1, u16, 2) = output.x;
    FIELD(arg1, u16, 6) = output.y;
    FIELD(arg1, u16, 0xA) = output.z;
    goto done;

state_one:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: Separate 32-byte call record and 8-byte output locals establish the 0x48 frame.
   Three long-lived arguments naturally occupy s1/s2/s0; true-space gotos recover both joins.
   Two 8-byte byte-array assignments encode retail's paired unaligned aggregate copies. */
