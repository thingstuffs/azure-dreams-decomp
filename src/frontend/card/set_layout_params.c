#include "frontend/card/message_display.h"
#include "common.h"
#include "frontend/card.h"

/* Sets four record fields to the supplied values. */
void set_layout_params(CardDevDialogDisplay *record, struct ObjectNodeHeader *owner, s32 value_08, s32 value_0c, s32 *result_slot) {
    record->owner = owner;
    record->layout_index = value_08;
    record->mode = value_0c;
    record->result_slot = result_slot;
}
