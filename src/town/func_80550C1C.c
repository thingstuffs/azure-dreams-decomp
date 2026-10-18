#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017A74[];
void *call_set_global_pointer(void) { return D_80017A74; }
