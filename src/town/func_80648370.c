#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017B10[];
void *select_record_pointer_by_status(void) { return D_80017B10; }
