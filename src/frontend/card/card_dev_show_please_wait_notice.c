#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Forwards the target and value to init_card_message_object with both selectors set to 2. */
void card_dev_show_please_wait_notice(s32 target, s32 value) {
    init_card_message_object(target, 2, 2, value);
}
