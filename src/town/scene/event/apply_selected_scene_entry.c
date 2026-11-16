#include "modules/town_ovl_64b0c0.h"
#include "town/scene/motion.h"

/* Passes the value and line to the handler with its fixed data tables. */
s32 apply_selected_scene_entry(s32 value, s32 unused, s32 line)
{
    return apply_entry_position(D_8001775C, D_80017890, value, line);
}
