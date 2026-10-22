/* Selection-menu teardown and saved-value submission through shared output state. */
#include "slus/saved_value_b98.h"

s32 saved_value_output_enabled = 1;
s32 selection_menu_saved_value = 0;

#include "../build/partition_sources/code__saved_value_b98.c"
#include "w_80050DA8.c"
#include "w_80050E20.c"
