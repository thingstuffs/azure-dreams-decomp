#include "common.h"

extern u8 D_80081485;

/* Returns whether D_80081485 is zero. */
s32 check_global_data_byte_zero(void) {
    return D_80081485 == 0;
}
