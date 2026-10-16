#include "common.h"

/* TOWN file 0x3EAB90 (rowbase sweep_3EA000, delta 0x7FC31000; the local `j` lands inside this
 * function only at that base).  Same shape as the matched selector func_800162A4
 * (src/town/func_8032BAA4.c): reads only the third argument.  Evidence: docs/evidence/r121_rem_opus.md. */

extern u8 D_80017774[];
extern u8 D_8001601C[];

/* Pick one of two global records by the selector. */
u8 *func_8001BB90(s32 unused_a, s32 unused_b, s32 selector) {
    if (selector == 4) {
        return D_8001601C;
    }
    return D_80017774;
}
