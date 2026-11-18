#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Calls init_card_message_object for the target with fixed arguments 9, 0, and 0. */
void card_dev_show_insufficient_space_overwrite_advice(struct ObjectNodeHeader *target) {
    init_card_message_object(target, 9, 0, 0);
}
