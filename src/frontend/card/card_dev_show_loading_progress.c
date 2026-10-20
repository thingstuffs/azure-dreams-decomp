#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Dispatch operation 0xe in mode 2 with the supplied context and payload. */
void card_dev_show_loading_progress(s32 context, s32 payload) {
    init_card_message_object(context, 0xe, 2, payload);
}
