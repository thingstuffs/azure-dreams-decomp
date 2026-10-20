#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Calls init_card_message_object for the target with fixed arguments 9, 0, and 0. */
void card_dev_show_insufficient_space_overwrite_advice(s32 target) {
    init_card_message_object(target, 9, 0, 0);
}
