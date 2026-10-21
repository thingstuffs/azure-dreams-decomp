#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card.h"

/* Pass the target to init_card_message_object with code 0x13 and zero options. */
void card_dev_show_delete_failure_notice(s32 target) {
    init_card_message_object(target, 0x13, 0, 0);
}
