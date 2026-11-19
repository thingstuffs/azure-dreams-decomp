#include "frontend/card/message_display.h"
#include "common.h"
#include "frontend/card.h"

/* Sets four record fields to the supplied values. */
void set_layout_params(CardDevDialogDisplay *record, struct ObjectNodeHeader *owner, s32 value_08, s32 value_0c, s32 value_20) {
    record->owner = owner;
    record->layout_index = value_08;
    record->mode = value_0c;
    record->result_word = value_20;
}
