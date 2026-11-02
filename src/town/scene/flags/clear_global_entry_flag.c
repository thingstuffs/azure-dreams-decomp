#include "common.h"
#include "town/scene/flags.h"
#include "town/data.h"

/* Stores 0 in catalog_lookup_count. */
void clear_global_entry_flag(void) { catalog_lookup_count = 0; }
