#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Dispatch operation 6 in mode 2 with the supplied target and value. */
void card_dev_show_saving_progress(s32 target, s32 value) {
    init_card_message_object(target, 6, 2, value);
}
