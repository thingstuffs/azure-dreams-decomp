#include "common.h"

#include "frontend/card/message_object.h"   /* extern */
#include "frontend/card/message.h"

/* Forwards value to init_card_message_object with fixed arguments 7, 0, 0. */
void check_record_field_0x04_is_one(s32 value) {
    init_card_message_object(value, 7, 0, 0);
}
