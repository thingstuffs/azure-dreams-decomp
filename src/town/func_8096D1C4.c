#include "common.h"

extern u8 D_801269F8[];
__asm__(".set D_801269F8, 0x801269F8");

void func_8012565C(void *arg0) {
    volatile u8 *state = D_801269F8;

    state[9] -= 4;
    if (!(state[9] & 0xF)) {
        *((s8 *)arg0 + 0xA) = 8;
    }
}
