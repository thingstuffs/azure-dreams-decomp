#include "common.h"

u8 *init_card_message_object();   /* extern */

/* Dispatch operation 5 for the target with one value. */
void func_8001C194(s32 target, s32 value) {
    init_card_message_object(target, 5, 1, value);
}
