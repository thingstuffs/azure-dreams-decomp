#include "modules/ovmovie_libpress.h"


/* Read status bit 24, or refresh and hand back the refresher's status. */
s32 func_8017791C(s32 read_status_bit) {
    if (read_status_bit != 0) {
        return (func_80177CF0() >> 0x18) & 1;
    }
    return func_80177C58();
}
