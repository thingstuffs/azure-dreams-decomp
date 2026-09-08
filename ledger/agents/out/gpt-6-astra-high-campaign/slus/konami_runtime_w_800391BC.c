#include "common.h"

#include "common.h"

extern void ClearImage(void *rect, s32 r, s32 g, s32 b);

/* Handles event-script image clearing by zeroing two state fields and clearing the rectangle to black. */
void func_800391BC(void *vm_state) {
    *(s16 *)((u8 *)vm_state + 0x20) = 0;
    *(s16 *)((u8 *)vm_state + 0x22) = 0;
    ClearImage(vm_state, 0, 0, 0);
}
