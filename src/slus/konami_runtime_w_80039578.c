#include "common.h"

typedef struct Func80039578State {
    u8 pad_00[0x10];
    void (*func_10)(void *);
    u8 pad_14[0x04];
    u16 half_18;
    u8 pad_1A[0x02];
    u8 *read_ptr;
} Func80039578State;

extern void func_80038128(void *arg0);

/* Read a little-endian 16-bit value and set the state's callback. */
void func_80039578(Func80039578State *state) {
    u32 addr_or_high = (u32)state->read_ptr;
    u32 read_addr = addr_or_high;
    u32 low_byte = *(u8 *)addr_or_high;

    addr_or_high = *(u8 *)(addr_or_high + 1);
    state->read_ptr = (u8 *)(read_addr + 2);
    state->func_10 = func_80038128;
    state->half_18 = (u16)(low_byte + (addr_or_high << 8));
}
