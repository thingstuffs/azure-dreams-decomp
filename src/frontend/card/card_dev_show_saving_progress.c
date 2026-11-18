#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Dispatch operation 6 in mode 2 with the supplied target and value. */
void card_dev_show_saving_progress(struct ObjectNodeHeader *target, s32 value) {
    init_card_message_object(target, 6, 2, value);
}
