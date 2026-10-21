#include "common.h"
#include "m2c_compat.h"

extern s32 script_rescan_request;
void request_entry_rescan(void) { script_rescan_request = 1; }
