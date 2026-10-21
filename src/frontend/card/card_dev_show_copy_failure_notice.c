#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card.h"

/* Passes value to init_card_message_object with fixed arguments 0x10, 0, 0. */
void card_dev_show_copy_failure_notice(s32 value) {
    init_card_message_object(value, 0x10, 0, 0);
}
