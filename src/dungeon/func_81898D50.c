#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Increments the referenced object's counter, updates the target, and flags pending status. */
void func_80024550(void *object_ref, s32 unused, void *target) {
    u8 *object;

    object = *(u8 **)((u8 *)object_ref + 0x0);
    *(u16 *)(object + 0x14) += 1;
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)object_ref - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
