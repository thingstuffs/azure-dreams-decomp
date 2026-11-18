#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Forward the context and value with fixed arguments 0x12 and 1. */
void card_dev_show_delete_confirmation(struct ObjectNodeHeader *context, s32 value) {
    init_card_message_object(context, 0x12, 1, value);
}
