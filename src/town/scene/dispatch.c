#include "town/scene/dispatch.h"
#include "town/scene/motion.h"
#include "town/scene.h"

/* Passes the value and line to the handler with its fixed data tables. */
s32 apply_selected_scene_entry(TownObjectSet *value, s32 unused, s32 line) {
    /* D_80017760 is also the u8 * TownTerminalData of attach_scene_event_data.c; here it is read as position entries. */
    return apply_entry_position((struct ScenePositionEntry *)D_80017760, D_800178C0, value, line);
}
