#include "slus/sound_register_helpers.h"

/* Replaces status bits 0x70000 with 0x30000 when use_status_3 is nonzero, otherwise 0x50000. */
void set_driver_status_bits(s32 use_status_3) {
    *D_80079968 &= ~0x70000;
    if (use_status_3) {
        *D_80079968 |= 0x30000;
    } else {
        *D_80079968 |= 0x50000;
    }
}
