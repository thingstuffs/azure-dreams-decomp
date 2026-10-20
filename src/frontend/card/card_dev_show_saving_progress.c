#include "common.h"

#include "frontend/card/message_object.h"   /* extern */

/* Dispatch operation 6 in mode 2 with the supplied target and value. */
void card_dev_show_saving_progress(s32 target, s32 value) {
    init_card_message_object(target, 6, 2, value);
}
