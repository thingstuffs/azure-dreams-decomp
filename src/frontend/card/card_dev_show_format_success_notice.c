#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card.h"

/* Calls init_card_message_object with the target and fixed arguments (13, 0, 0). */
void card_dev_show_format_success_notice(s32 target) {
    init_card_message_object(target, 0xd, 0, 0);
}
