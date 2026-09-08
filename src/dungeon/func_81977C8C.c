#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Increment the object's counter, update state, and propagate status flags. */
void func_81977C8C(void *object_slot, s32 unused, void *state) {
    u8 *object;

    object = *(u8 **)((u8 *)object_slot + 0x0);
    *(u16 *)(object + 0x1A) += 1;
    func_800478B8(state);
    if (*(u16 *)((u8 *)state + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_slot - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
