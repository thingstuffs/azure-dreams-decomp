#include "modules/town_ovl_64b0c0.h"
#include "modules/town_ovl_64b0c0.h"
#include "town/scene/motion.h"

/* Passes the value and line to the handler with its fixed data tables. */
s32 process_value_with_fixed_tables(s32 value, s32 unused, s32 line)
{
    return apply_entry_position(D_8001775C, D_80017890, value, line);
}
