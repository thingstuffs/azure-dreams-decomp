#include "common.h"

extern void func_800478B8(void *arg0);
extern s32 D_800814A0;

/* Increment the linked object's counter, process the target, and propagate its status flags. */
void func_80024224(void *entry, s32 unused, void *target) {
    u8 *linked_obj;

    linked_obj = *(u8 **)((u8 *)entry + 0xC);
    *(u16 *)(linked_obj + 0x16) += 1;
    func_800478B8(target);
    if (*(u16 *)((u8 *)target + 0x14) & 0x6000) {
        *(u16 *)((u8 *)entry - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
