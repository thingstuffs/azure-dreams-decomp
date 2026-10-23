#include "common.h"
#include "m2c_compat.h"

extern u8 D_800181F7[];
/* Returns the current value of D_800181F7. */
void *select_db_8_handler(void) { return D_800181F7; }
