#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Forward the target and value to init_card_message_object with selectors 0 and 1. */
void card_dev_show_format_confirmation(s32 target, s32 value) {
    init_card_message_object(target, 0, 1, value);
}
