#include "common.h"
#include "m2c_compat.h"

extern s32 D_800178A8;
/* Stores 1 in D_800178A8. */
void request_eligible_entry_rescan(void) { D_800178A8 = 1; }
