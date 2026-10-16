#include "common.h"

extern u8 D_801269F8[];

/* Decrease the shared byte by four and enter state eight when its low nibble clears. */
void townScrollCatalogTextUp(void *controller) {
    u8 *state = D_801269F8;

    state[9] -= 4;
    if (state[9] % 16 == 0) {
        *((s8 *)controller + 0xA) = 8;
    }
}
