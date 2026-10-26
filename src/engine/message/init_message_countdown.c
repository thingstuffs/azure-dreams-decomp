#include "common.h"
#include "engine/message.h"
#include "engine/script.h"

#include "common.h"

typedef struct S_8003832C_0 {
    u8 pad_00[0x10];
    void (*unk_10)(struct S_80038368_0 *);
    u8 pad_14[0x4];
    s16 unk_18;
} S_8003832C_0;   /* arg0 in func_8003832C */

void read_message_byte(ScriptReader *state);                            /* extern */

/* Initialize the context and set its next handler and state. */
void consume_message_byte_and_start_countdown(S_8003832C_0 *context) {
    read_message_byte((ScriptReader *)context);
    context->unk_18 = 5;
    context->unk_10 = &decrement_countdown_and_switch_b;
}
