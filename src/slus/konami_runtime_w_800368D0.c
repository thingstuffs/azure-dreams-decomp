#include "common.h"

#include "common.h"

typedef void (*Callback)(void);

extern void func_800368F8(void);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

void func_800368D0(void *arg0) {
    u8 *base;
    s16 offset;

    base = FIELD(arg0, u8 *, 0x44);
    offset = FIELD(arg0, s16, 0x4A);
    FIELD(base + offset, u8, 0x50) = 0xFF;
    FIELD(arg0, Callback, 0x68) = func_800368F8;
}
