#include "common.h"
#include "m2c_compat.h"

extern u8 D_8001B14C[];
void *get_shared_entry_buffer_y(void) { return D_8001B14C; }
