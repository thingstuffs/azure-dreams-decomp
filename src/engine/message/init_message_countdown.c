#include "common.h"

#include "common.h"

typedef struct S_8003832C_0 {
    u8 pad_00[0x10];
    s32 * unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_8003832C_0;   /* arg0 in func_8003832C */


typedef struct {
    u8 pad_00[0x1C];
    u8 *stream;
    u8 pad_20[0x60];
    u8 *buffer;
} Func80039AF0State;
void read_message_byte(Func80039AF0State *state);                            /* extern */
extern s32 decrement_countdown_and_switch_b;

/* Initialize the context and set its next handler and state. */
void consume_message_byte_and_start_countdown(S_8003832C_0 *context) {
    read_message_byte((Func80039AF0State *)context);
    context->unk_18 = 5;
    context->unk_10 = &decrement_countdown_and_switch_b;
}
