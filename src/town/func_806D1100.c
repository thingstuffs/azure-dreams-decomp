#include "common.h"
#include "m2c_compat.h"

extern u8 D_800173CC[];
extern void *D_80017480;
void invoke_callback_and_set_shared_pointer(void) { D_80017480 = D_800173CC; }
