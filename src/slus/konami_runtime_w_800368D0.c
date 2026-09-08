#include "common.h"

#include "common.h"

typedef void (*Callback)(void);

extern void func_800368F8(void);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

/* Writes 0xFF to the selected buffer byte and selects func_800368F8 as the callback. */
void func_800368D0(void *state) {
    u8 *buffer;
    s16 byte_offset;

    buffer = FIELD(state, u8 *, 0x44);
    byte_offset = FIELD(state, s16, 0x4A);
    FIELD(buffer + byte_offset, u8, 0x50) = 0xFF;
    FIELD(state, Callback, 0x68) = func_800368F8;
}
