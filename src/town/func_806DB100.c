#include "common.h"
#include "m2c_compat.h"

extern u8 D_800175B8[];
extern void *D_8001766C;
void invoke_callback_and_set_shared_pointer(void) { D_8001766C = D_800175B8; }
