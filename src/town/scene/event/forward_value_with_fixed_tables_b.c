#include "modules/town_ovl_64f0c0.h"
#include "town/scene/motion.h"
#include "town/scene.h"

/* Passes the value and line to the handler with its fixed strings. */
void apply_selected_scene_entry(TownObjectSet *value, s32 unused, s32 line)
{
    (void)unused;
    apply_entry_position(D_80017568, D_80017658, value, line);
}
