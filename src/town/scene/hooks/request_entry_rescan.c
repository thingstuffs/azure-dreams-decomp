#include "common.h"
#include "m2c_compat.h"
#include "town/scene/hooks.h"
#include "town/data.h"

/* Stores 1 in script_rescan_request. */
void request_entry_rescan(void) { script_rescan_request = 1; }
