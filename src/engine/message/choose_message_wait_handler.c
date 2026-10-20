#include "common.h"

#include "common.h"

typedef struct S_80038288_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x8];
    u8 * unk_1C;
} S_80038288_0;   /* arg0 in choose_message_wait_handler */


s32 play_message_confirmation_sound();                              /* extern */
s32 func_80053EF0();                         /* extern */
void finish_message_when_idle();
void consume_message_byte_and_start_countdown();

/* Selects the context's next handler based on its current byte when updates are allowed. */
void choose_message_wait_handler(S_80038288_0 *context) {
    s32 *next_handler;

    if (func_80053EF0(4) != 0x100) {
        if (play_message_confirmation_sound(*context->unk_1C) != 0) {
            next_handler = &finish_message_when_idle;
        } else {
            next_handler = &consume_message_byte_and_start_countdown;
        }
        context->unk_10 = next_handler;
    }
}
