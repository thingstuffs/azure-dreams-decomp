#include "common.h"

#include "common.h"

typedef struct S_80038288_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x8];
    u8 * unk_1C;
} S_80038288_0;   /* arg0 in choose_message_wait_handler */


s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
void finish_message_when_idle();
void func_8003832C();

/* Selects the context's next handler based on its current byte when updates are allowed. */
void choose_message_wait_handler(S_80038288_0 *context) {
    s32 *next_handler;

    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*context->unk_1C) != 0) {
            next_handler = &finish_message_when_idle;
        } else {
            next_handler = &func_8003832C;
        }
        context->unk_10 = next_handler;
    }
}
