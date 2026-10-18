#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Dispatch operation 0xe in mode 2 with the supplied context and payload. */
void func_8001C1E4(s32 context, s32 payload) {
    init_card_message_object(context, 0xe, 2, payload);
}
