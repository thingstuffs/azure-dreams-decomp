#include "common.h"

typedef struct {
    u8 unk0[0x18];
    s16 unk18;
    u16 unk1A;
} GlobalADBC;

extern GlobalADBC D_8006ADBC;

/* Check whether unk18 is 12 and unk1A is between 37 and 41. */
s32 func_8009FF50(void) {
    GlobalADBC *global_state = &D_8006ADBC;

    if (global_state->unk18 == 12) {
        if ((u32)(global_state->unk1A - 37) < 5) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: Frameless leaf with a named struct pointer holds D_8006ADBC in $a0;
   signed/unsigned halfword fields reproduce lh/lhu. Nested positive early return
   preserves the retail conditional branch, constant delay slot, and zero fallthrough. */
