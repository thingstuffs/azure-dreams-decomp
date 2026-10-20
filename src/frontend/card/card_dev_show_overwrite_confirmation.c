#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Dispatch operation 5 for the target with one value. */
void card_dev_show_overwrite_confirmation(s32 target, s32 value) {
    init_card_message_object(target, 5, 1, value);
}
