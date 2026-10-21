#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card.h"

/* Forwards a target and value to init_card_message_object with fixed parameters 4 and 2. */
void card_dev_show_formatting_progress(s32 target, s32 value) {
    init_card_message_object(target, 4, 2, value);
}
