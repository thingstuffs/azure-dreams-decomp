#include "common.h"
#include "dungeon/actor/object.h"
#include "shared/record_ptrs.h"

#ifndef NULL
#define NULL 0
#endif


/* Return whether an enabled object has either linked object flagged with bit 0x10000. */
s32 is_linked_object_flagged_10000(void *object) {
    s32 slot_index;
    void *linked_object;
    void *slot_base;

    if (*(s32 *)((u8 *)object + 0x14) & 0x4000) {
        slot_index = 1;
        slot_base = (u8 *)dungeon_actor_ring_anchor + 4;
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
