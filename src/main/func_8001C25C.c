#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Invoke operation 0xb for the target with both options cleared. */
void func_8001C25C(s32 target) {
    init_card_message_object(target, 0xb, 0, 0);
}
