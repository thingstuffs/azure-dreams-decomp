#include "modules/town_ovl_6510c0.h"
#include "town/scene/motion.h"
#include "town/scene.h"

/* Passes the value and line to the handler with its fixed data tables. */
s32 apply_selected_scene_entry(TownObjectSet *value, s32 unused, s32 line)
{
    return apply_entry_position(D_800173B4, D_80017474, value, line);
}
