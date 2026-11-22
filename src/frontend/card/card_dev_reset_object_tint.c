#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/slot_marker.h"

/* Set the object's default value and clear its linked state if present. */
void card_dev_reset_object_tint(CardDevSlotWindow *object) {
    if (object != NULL) {
        object->body.frame_block.words[0] = 0x606868;
        object->body.entries[9]->display.payload.word = 0;
    }
}
