#include "common.h"

#include "common.h"
#include "engine/message.h"

typedef struct S_80038708_0 {
    u8 pad_00[0x10];
    void (*unk_10)(struct Func80038A10State *);
    u8 pad_14[0x1E];
    s8 unk_32;
} S_80038708_0;   /* arg0 in run_indexed_handler_and_set_next */


extern u8 D_800DCF54[];

/* Calls the record's indexed handler, then sets its next handler to update_message_window. */
void run_indexed_handler_and_set_next(S_80038708_0 *record) {
    ((s32 (*)())(*(s32 *)((u8 *)(&D_800DCF54) + ((record->unk_32) * 4))))();
    record->unk_10 = &update_message_window;
}
