#include "common.h"
#include "m2c_compat.h"

extern u8 D_800178A4[];
/* Returns the current value of D_800178A4. */
void *run_event_403_get_buffer(void) { return D_800178A4; }
