#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card.h"

/* Forwards the input to init_card_message_object with arguments 0xC, 0, and 0. */
void card_dev_show_format_failure_notice(s32 input) {
    init_card_message_object(input, 0xc, 0, 0);
}
