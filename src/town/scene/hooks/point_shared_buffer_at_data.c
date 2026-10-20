#include "common.h"
#include "m2c_compat.h"

extern u8 D_80017EFC[];
extern void *D_80017FC0;
void point_shared_buffer_at_data(void) { D_80017FC0 = D_80017EFC; }
