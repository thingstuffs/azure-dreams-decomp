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

/* Masks a0 to 16 bits and forwards it to func_80040AA0, then stores the
 * remaining four arguments into D_80082E60's field_10..field_16 (s16 slots). */
void func_80041094(s32 a0, s16 a1, s16 a2, s16 a3, s32 a4)
{
    func_80040AA0((u16)a0);
    D_80082E60.field_10 = a1;
    D_80082E60.field_12 = a2;
    D_80082E60.field_14 = a3;
    D_80082E60.field_16 = a4;
}
