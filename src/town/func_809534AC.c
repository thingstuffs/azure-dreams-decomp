#include "common.h"
#include "shared/object_flags.h"


/* Propagate bit 15 from the linked record when the record status is zero. */
void propagate_linked_flag_if_clear(void *record) {
    void *linked_record = *(void **)((u8 *)record + 0xC);

    if (*(s16 *)record == 0 &&
        (*(u16 *)((u8 *)linked_record + 4) & 0x8000) != 0) {
        *(u16 *)((u8 *)record - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
