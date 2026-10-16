#include "common.h"

extern u8 D_801269F8[];

/* Increase the shared byte by four and enter state eight when its low nibble clears
 * (the scroll-down partner of townScrollCatalogTextUp, src/town/func_8096D1C4.c). */
void func_80125694(void *controller) {
    u8 *state = D_801269F8;

    state[9] += 4;
    if (state[9] % 16 == 0) {
        *((s8 *)controller + 0xA) = 8;
    }
}
