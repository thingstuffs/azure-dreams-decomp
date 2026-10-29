#include "common.h"
#include "town/player.h"

extern s32 D_80100E2C[];

/* Read and clear the stored value, returning its lower 31 bits. */
s32 read_and_clear_stored_value(void) {
    s32 stored_value = D_80100E2C[0];
    D_80100E2C[0] = 0;
    return stored_value & 0x7FFFFFFF;
}
