#include "frontend/card/slot_marker.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

/* Address-taken via %hi/%lo — declare >8B so codegen uses lui+addiu, not gp. */

void card_devkit_set_window_selection_marker(void *basePtr, s32 flag) {
    CardMenuDisplayNode *targetPtr;
    CardDevSlotMarkerPrefix *panel;

    panel = basePtr;

    if (basePtr != 0) {
        panel->unk_1C0 = 0x808080;
        targetPtr = panel->marker;
        if (flag != 0) {
            targetPtr->payload.data = &D_80083840;
        } else {
            targetPtr->payload.word = 0;
        }
        targetPtr->block->fields.x = 0x60;
        targetPtr->block->fields.y = 0x18;
    }
}
