#include "slus/command_slots_81554.h"

extern void func_800352B4(void);

/* Marks the current registration slot, advances the slot counter, and calls two helpers. */
void func_8004E130(void)
{
    s32 slot_index;
    s32 *slot;

    slot_index = D_80081554 & 0xF;
    slot = &D_80083D98[slot_index];
    D_80081554 = slot_index;
    D_80081558 = slot_index;
    *slot = 1;
    D_80081554 = slot_index + 1;
    func_8003528C((s32)slot);
    func_800352B4();
}
