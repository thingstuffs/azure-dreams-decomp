#include "common.h"
#include "m2c_compat.h"

extern s32 D_80017594;
void request_entry_rescan(void) { D_80017594 = 1; }
