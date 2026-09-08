#include "common.h"

extern s32 D_800834B8[2];
extern s32 D_80097D2C;
extern s32 D_80097EA0;
extern s32 D_800814A0[3];
extern s32 D_80083780[3];
extern s32 D_800D0428;

extern void func_80033D08(void *arg0);

/* Copy the adjusted vector when state references match; otherwise process and flag the object. */
void func_800A8248(void *object, s32 *out_vector)
{
    s32 *state_refs = D_800834B8;

    if ((state_refs[0] != (s32)&D_80097D2C) ||
        (state_refs[1] != (s32)&D_80097EA0)) {
        func_80033D08(object);
        *(u16 *)((u8 *)object - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    out_vector[0] = D_80083780[0];
    out_vector[1] = D_80083780[1];
    out_vector[2] = D_80083780[2] + D_800D0428;
}
