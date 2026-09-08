#include "common.h"

/* Decreases the target's 16-bit value at offset 0x18 by four. */
void func_800A1FEC(void *unused_0, void *unused_1, void *target) {
    *(u16 *)((u8 *)target + 0x18) -= 4;
}
