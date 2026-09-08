#include "common.h"

typedef struct Func800395B0State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x08];
    u8 *read_ptr;
    u8 pad_20[0x10];
    u16 half_30;
} Func800395B0State;

extern void func_80038394(void *arg0);

/* Reads a little-endian 16-bit script operand and selects the next state handler. */
void func_800395B0(Func800395B0State *state) {
    u32 addr_or_high = (u32)state->read_ptr;
    u32 start_addr = addr_or_high;
    u32 low_byte = *(u8 *)addr_or_high;

    addr_or_high = *(u8 *)(addr_or_high + 1);
    state->read_ptr = (u8 *)(start_addr + 2);
    state->func_10 = func_80038394;
    state->half_30 = (u16)(low_byte + (addr_or_high << 8));
}
