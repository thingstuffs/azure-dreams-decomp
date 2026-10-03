#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


/* Adds 100 to the stored value, divides by 100, and caps the result at ten. */
s32 func_8054FB14(void) {
    u32 value;

    value = (D_80016000->unk_38->unk_2D5C + 0x64U) / 100U;
    if ((s32)value >= 0xB) {
        value = 0xAU;
    }
    return value;
}
