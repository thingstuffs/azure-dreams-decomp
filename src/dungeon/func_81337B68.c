#include "common.h"

extern s32 D_80175D78[];

/* Clear one state field and increment the counter for each of sixteen objects. */
void func_8016EB68(void) {
    s32 *object_entry;
    s32 object_index;
    void *state;
    u16 count;

    object_index = 0;
    object_entry = D_80175D78;
    do {
        state = *object_entry + 0x20;
        count = *(u16 *)(state + 0x12);
        
        *(s16 *)(state + 0x18) = 0;
        *(u16 *)(state + 0x12) = count + 1;
        object_entry += 1;
        object_index += 1;
    } while (object_index < 0x10);
}

/* MECHANISM: Frameless leaf loop retained; an explicit u16 temp exposes the retail RMW lifetime.
   The v0 pin+keep preserves the load-delay nop and places the increment below lhu.
   A fence after the zero store leaves a0 += 4 available for the loop branch delay slot. */
