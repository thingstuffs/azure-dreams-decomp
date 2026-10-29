#include "town/scene.h"
#include "town/player.h"
#include "town/scene/flags.h"


/* Update the current script flag when the linked value passes the check. */
s32 process_entry_linked_nonzero(void *object, s32 entry_index)
{
    if (get_entry_linked_value() != 0) {
        set_active_entry_script_flag();
    }
    return process_checked_scene_entry(object, entry_index);
}
