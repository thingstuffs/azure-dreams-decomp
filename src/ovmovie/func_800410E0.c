#include "modules/ovmovie_libpress.h"


/* Read status bit 29, or refresh and hand back the refresher's status. */
s32 func_801778E0(s32 read_status_bit) {
    if (read_status_bit != 0) {
        return (func_80177CF0() >> 0x1D) & 1;
    }
    return func_80177BC0();
}
