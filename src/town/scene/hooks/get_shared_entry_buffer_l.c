#include "common.h"
#include "m2c_compat.h"

extern u8 D_80018F50[];
/* Returns the current value of D_80018F50. */
void *get_shared_entry_buffer_l(void) { return D_80018F50; }
