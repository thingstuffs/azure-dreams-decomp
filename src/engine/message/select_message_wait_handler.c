#include "common.h"

#include "common.h"
#include "records/Rec_func_800381D0_arg0.h"


s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
void choose_message_wait_handler();
void finish_message_when_idle();
void func_8003832C();

/* Selects the next handler based on runtime status and the context byte. */
s32 *select_message_wait_handler(Rec_func_800381D0_arg0 *context) {
    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*context->unk_1C) != 0) {
            return &finish_message_when_idle;
        }
        return &func_8003832C;
    }
    return &choose_message_wait_handler;
}
