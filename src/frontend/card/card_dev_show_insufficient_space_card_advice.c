#include "common.h"

#include "frontend/card/message.h"
#include "frontend/card.h"

/* Forwards value to init_card_message_object with fixed arguments 10, 0, and 0. */
void card_dev_show_insufficient_space_card_advice(struct ObjectNodeHeader *value) {
    init_card_message_object(value, 0xa, 0, 0);
}
