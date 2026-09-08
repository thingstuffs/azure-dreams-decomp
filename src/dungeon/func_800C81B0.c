#include "common.h"

/* Object shape as seen by func_800CD910: a 32-bit handle/value field at
 * offset 0x00 and a 16-bit countdown field at offset 0x06. The 16-bit
 * "used"/flags field one halfword before the object (offset -2) is the
 * same shape referenced by the D_800814A0 sibling family (code5.c,
 * code9.c, w_8004FE78.c, ...). */
typedef struct S_800C81B0_a0 {
    s32 field_0;            /* 0x00 */
    u8 pad4[0x6 - 0x4];
    u16 field_6;             /* 0x06 */
} S_800C81B0_a0;

/* Shared counter/flags block; only the 16-bit field at offset 0xA is
 * touched here. */
typedef struct {
    u8 pad0[0xA];
    u16 field_A;             /* 0x0A */
} S_80083460_t;

extern S_80083460_t D_80083460;
extern int D_800814A0;
extern void func_800CD994(s32 arg0, s32 arg1);

/* Ticks the object's countdown, releasing its handle and updating the shared counter and flags on expiry. */
void func_800CD910(S_800C81B0_a0 *object)
{
    s16 countdown;

    countdown = --object->field_6;
    if (countdown <= 0) {
        func_800CD994(object->field_0, 0x10);
        D_80083460.field_A--;
        ((u16 *)object)[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
