#include "town/menu/window.h"

/* Return the high-bit flag from D_80100AF0->unk_1E. */
s32 get_current_high_bit_flag(void) {
    return D_80100AF0->unk_1E & 0x8000;
}
