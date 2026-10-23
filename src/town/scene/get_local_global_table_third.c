#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017510;
/* Stores 1 in D_80017510. */
void get_local_global_table(void) { D_80017510 = 1; }
