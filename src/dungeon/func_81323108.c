#include "common.h"

void func_8016A908(u8 *arg0) {
    u8 flags;
    u16 status;

    flags = arg0[0x71];
    status = *(u16 *)(arg0 + 0x46);
    arg0[0x6D] = 0;
    arg0[0x71] = flags & 0x7F;
    *(u16 *)(arg0 + 0x46) = status & 0x7FFF;
}
