#include "modules/town_ovl_64f0c0.h"
#include "modules/town_ovl_64f0c0.h"
#include "town/scene/motion.h"

/* Passes the value and line to the handler with its fixed strings. */
void process_value_with_fixed_tables(s32 value, s32 unused, s32 line)
{
    (void)unused;
    apply_entry_position(D_80017568, D_80017658, value, line);
}
