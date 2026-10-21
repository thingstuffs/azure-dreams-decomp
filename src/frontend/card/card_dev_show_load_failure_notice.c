#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card.h"

/* Invoke operation 0xb for the target with both options cleared. */
void card_dev_show_load_failure_notice(s32 target) {
    init_card_message_object(target, 0xb, 0, 0);
}
