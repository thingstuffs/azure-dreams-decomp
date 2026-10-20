#include "town/scene/dispatch.h"
#include "town/scene/dispatch.h"

/* Passes the value and line to the handler with its fixed data tables. */
s32 process_value_with_fixed_tables(s32 value, s32 unused, s32 line)
{
    return get_flag_test_table_address(D_80017760, D_800178C0, value, line);
}
