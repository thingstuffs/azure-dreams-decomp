#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 D_800E3D7C;

/* Return whether an enabled object has either linked object flagged with bit 0x10000. */
s32 func_800C80F0(void *object) {
    s32 slot_index;
    void *linked_object;
    void *slot_base;

    if (*(s32 *)((u8 *)object + 0x14) & 0x4000) {
        slot_index = 1;
        slot_base = D_800E3D7C + 4;
        do {
            linked_object = *(void **)((u8 *)slot_base + 0xAC);
            if ((linked_object != NULL) && (*(s32 *)((u8 *)linked_object + 0x54) & 0x10000)) {
                return 1;
            }
            slot_index -= 1;
            slot_base -= 4;
        } while (slot_index >= 0);
    }
    return 0;
}
