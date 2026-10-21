#include "common.h"

extern s16 catalog_lookup_count;
void clear_global_entry_flag(void) { catalog_lookup_count = 0; }
