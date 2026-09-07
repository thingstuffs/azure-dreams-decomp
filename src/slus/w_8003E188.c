#include "common.h"

/* Sets a 2-bit packed field in byte-array D_80013614: byte index = (s16)arg0 >> 2,
 * sub-field shift = (arg0 & 3) * 2 bits; value = (arg1's low 16 bits != 0) ? 3 : 1,
 * OR'd (not cleared) into place. */
extern u8 D_80013614[16];

void setPacked2bitFlag(s32 arg0, s32 arg1) {
    u8 *p;
    s32 idx;
    s32 shift;
    u8 old;
    s32 val;

    p = D_80013614;
    idx = (s16)arg0 >> 2;
    p = p + idx;
    shift = (arg0 & 3) << 1;
    old = *p;
    val = 1;
    if ((arg1 << 16) != 0) {
        val = 3;
    }
    *p = old | (val << shift);
}
