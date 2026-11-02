#include "frontend/card/save_slot.h"
#include "common.h"
#include "frontend/card.h"

typedef struct { u8 pad[0x7C]; s32 index; } Owner;
extern CardSaveSlot card_slot_header_cache[];
/*
 * Builds selected-slot details for a nonzero cached card header, or the memory-task text for an
 * empty header.
 */
void select_memory_task_exit(Owner *owner) {
    if (card_slot_header_cache[owner->index].words[0]) {
        card_build_selected_slot_details(owner);
    } else {
        build_memory_task_text((s32)owner);
    }
}
