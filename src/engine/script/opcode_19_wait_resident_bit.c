#include "common.h"
#include "engine/message.h"
#include "engine/script.h"

typedef struct Func800395B0State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x10];
    u16 half_30;
} Func800395B0State;

/* Opcode 0x13: Wait until the event flag given by the 16-bit operand is set. */
void script_wait_flag_set(Func800395B0State *state) {
    u32 addr_or_high = (u32)state->read_ptr;
    u32 start_addr = addr_or_high;
    u32 low_byte = *(u8 *)addr_or_high;

    addr_or_high = *(u8 *)(addr_or_high + 1);
    state->read_ptr = (u8 *)(start_addr + 2);
    state->func_10 = wait_message_resident_bit;
    state->half_30 = (u16)(low_byte + (addr_or_high << 8));
}
