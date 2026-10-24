#include "town/scene.h"
#include "town/player.h"


/* Set the indexed entry flag while the fixed script flag is enabled. */
s32 set_entry_flag_if_5c7(void *object, s32 entry_index)
{
    if (get_scene_script_flag_mask(0x5C7) != 0) {
        set_indexed_scene_entry_flag(object, entry_index);
        return 1;
    }
    return 0;
}
