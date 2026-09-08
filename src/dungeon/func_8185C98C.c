#include "common.h"

extern s32 func_800478B8();
extern s32 D_800814A0[3];

/* Increment the object counter, advance paired state values, and propagate status flags. */
void func_8185C98C(void *object_ref, void *unused, void *state) {
    void *object;
    u16 next_value;

    object = *(void **)object_ref;
    *(u16 *)((u8 *)object + 0x14) =
        (u16)(*(u16 *)((u8 *)object + 0x14) + 1);
    next_value = *(u16 *)((u8 *)state + 0x1E) + 0x800;
    *(u16 *)((u8 *)state + 0x1E) = next_value;
    *(u16 *)((u8 *)state + 0x1C) = next_value;
    func_800478B8(state);
    if (*(u16 *)((u8 *)state + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_ref - 2) =
            (u16)(*(u16 *)((u8 *)object_ref - 2) | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
