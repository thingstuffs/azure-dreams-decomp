/* Runtime callback-list reset, append and removal using a shared write cursor. */
#include "slus/list_cursor_e0.h"

void (**runtime_callback_write_cursor)(void) = 0;

#include "../build/partition_sources/code2__list_cursor_e0.c"
#include "../build/partition_sources/code__list_cursor_e0.c"
#include "w_80041134.c"
