#include "common.h"

/* Resets/rotates a subsystem state block: shifts D_800847D0's pending fields (0x10/0x14/0x31/0x33) into the active fields (0x8/0xC/0x30/0x32), zeroes the pending fields, re-arms D_80084858's counter/timer (field_C=3, field_10=0x80), and clears status bits 0x400/0x4000 in flags1 and 0x200 in flags2. */
typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u32 flags2;
    /* 0x08 */ u32 field8;
    /* 0x0C */ u32 fieldC;
    /* 0x10 */ u32 field10;
    /* 0x14 */ u32 field14;
    /* 0x18 */ u8 pad18[0x18];
    /* 0x30 */ u8 field30;
    /* 0x31 */ u8 field31;
    /* 0x32 */ u8 field32;
    /* 0x33 */ u8 field33;
} S_800847D0;

typedef struct S_80084858 {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s32 field_C;
    /* 0x10 */ s16 field_10;
} S_80084858;

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;

void func_80054C58(void) {
    S_800847D0 *a0 = &D_800847D0;
    u32 tmp8 = a0->field10;
    u32 tmpC = a0->field14;
    u8 tmp30 = a0->field31;
    u8 tmp32 = a0->field33;

    a0->field10 = 0;
    a0->field14 = 0;
    a0->field31 = 0;
    a0->field33 = 0;

    D_80084858.field_C = 3;
    D_80084858.field_10 = 0x80;

    a0->field8 = tmp8;
    a0->fieldC = tmpC;
    a0->field30 = tmp30;
    a0->field32 = tmp32;

    a0->flags1 &= ~0x400;
    a0->flags1 &= ~0x4000;
    a0->flags2 &= ~0x200;
}
