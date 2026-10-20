#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Dispatches operation 0xf in mode 2 with the supplied target and value. */
void card_dev_show_copying_progress(s32 target, s32 value) {
    init_card_message_object(target, 0xf, 2, value);
}
