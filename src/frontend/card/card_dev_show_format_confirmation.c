#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Open the format question (selectors 0 and 1); the answer is written to answer_slot. */
void card_dev_show_format_confirmation(struct ObjectNodeHeader *target, s32 *answer_slot) {
    init_card_message_object(target, 0, 1, answer_slot);
}
