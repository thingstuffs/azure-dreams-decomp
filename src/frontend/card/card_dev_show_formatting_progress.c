#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Forwards a target and value to init_card_message_object with fixed parameters 4 and 2. */
void card_dev_show_formatting_progress(struct ObjectNodeHeader *target, s32 *result_slot) {
    init_card_message_object(target, 4, 2, result_slot);
}
