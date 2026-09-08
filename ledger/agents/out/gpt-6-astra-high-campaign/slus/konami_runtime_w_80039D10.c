#include "common.h"

typedef struct Func80039D10State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x06];
    u8 byte_26;
    u8 byte_27;
} Func80039D10State;

extern void func_80038630(void *arg0);

/* Read an event-script byte and select func_80038630 as the handler. */
void func_80039D10(Func80039D10State *state) {
    u32 operand = (u32)state->read_ptr;
    u32 read_addr = operand;

    operand = *(u8 *)operand;
    state->read_ptr = (u8 *)(read_addr + 1);
    state->byte_27 = 0;
    state->func_10 = func_80038630;
    state->byte_26 = (u8)operand;
}
