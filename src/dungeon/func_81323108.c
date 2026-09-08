#include "common.h"

/* Clears the state byte and the high bits of the flags and status fields. */
void func_8016A908(u8 *state) {
    u8 flags;
    u16 status;

    flags = state[0x71];
    status = *(u16 *)(state + 0x46);
    state[0x6D] = 0;
    state[0x71] = flags & 0x7F;
    *(u16 *)(state + 0x46) = status & 0x7FFF;
}
