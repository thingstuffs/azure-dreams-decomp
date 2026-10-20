#include "common.h"

extern u8 D_800133C4;

/* event_fountain_chk: return the fountain event check flag. */
u8 event_fountain_chk(void) {
    return D_800133C4;
}
