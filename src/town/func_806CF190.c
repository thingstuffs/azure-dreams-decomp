#include "common.h"
#include "m2c_compat.h"

extern u8 D_800175B0[];
extern void *D_80017664;
void check_fixed_query_6_nonzero(void) { D_80017664 = D_800175B0; }
