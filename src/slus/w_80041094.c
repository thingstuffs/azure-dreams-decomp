#include "common.h"

/* View of the shared global struct D_80082E60 as seen by this function:
 * a block of four consecutive s16 fields at offsets 0x10/0x12/0x14/0x16
 * (position/state values set by this notify-style setter). */
typedef struct S_80082E60 {
    u8 pad0[0x10];
    s16 field_10;
    s16 field_12;
    s16 field_14;
    s16 field_16;
} S_80082E60;

extern S_80082E60 D_80082E60;

extern void func_80040AA0(u16 a0);

/* Forwards a 16-bit notification value and updates four shared state fields. */
void func_80041094(s32 notify_value, s16 state_10, s16 state_12, s16 state_14, s32 state_16)
{
    func_80040AA0((u16)notify_value);
    D_80082E60.field_10 = state_10;
    D_80082E60.field_12 = state_12;
    D_80082E60.field_14 = state_14;
    D_80082E60.field_16 = state_16;
}
