#include "common.h"
#include "shared/object_flags.h"
#include "town/minigame/state.h"


/* Propagate bit 15 from the linked record when the record status is zero. */
void propagate_linked_flag_if_clear(TerminalSceneTextObject *record) {
    void *linked_record = record->owner;

    if (record->state.s == 0 &&
        (*(u16 *)((u8 *)linked_record + 4) & 0x8000) != 0) {
        *(u16 *)((u8 *)record - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
