#include "common.h"

extern u8 D_801269F8[];
__asm__(".set D_801269F8, 0x801269F8");

/* Decrease the shared byte by four and enter state eight when its low nibble clears. */
void func_8012565C(void *controller) {
    volatile u8 *state = D_801269F8;

    state[9] -= 4;
    if (!(state[9] & 0xF)) {
        *((s8 *)controller + 0xA) = 8;
    }
}
