#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Mark special object status locally and globally, then process the object. */
void func_800D79B0(u16 *state, void *unused, u16 *object) {
    if (*(u16 *)((u8 *)object + 0x14) & 0x6000) {
        u16 *state_flags = (u16 *)((u8 *)state - 2);
        *state_flags = (u16)(*state_flags | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
    func_800478B8(object);
}
