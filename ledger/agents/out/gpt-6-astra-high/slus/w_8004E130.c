#include "common.h"

extern s32 D_80081554;
extern s32 D_80081558;
extern void *D_80083D98[32];

extern void func_8003528C(void);
extern void func_800352B4(void);

/* Marks the current registration slot, advances the slot counter, and calls two helpers. */
void func_8004E130(void)
{
    s32 slot_index;
    void **slot;

    slot_index = D_80081554 & 0xF;
    slot = &D_80083D98[slot_index];
    D_80081554 = slot_index;
    D_80081558 = slot_index;
    *slot = (void *)1;
    D_80081554 = slot_index + 1;
    func_8003528C();
    func_800352B4();
}
