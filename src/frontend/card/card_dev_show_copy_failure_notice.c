#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Passes value to init_card_message_object with fixed arguments 0x10, 0, 0. */
void card_dev_show_copy_failure_notice(struct ObjectNodeHeader *value) {
    init_card_message_object(value, 0x10, 0, 0);
}
