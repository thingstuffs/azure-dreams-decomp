#include "town/scene.h"
#include "town/player.h"


/* Update the current script flag when the linked value passes the check. */
s32 process_entry_linked_five(void *object, s32 entry_index)
{
    if (read_entry_linked_value() >= 5) {
        mark_active_entry_script_flag();
    }
    return process_checked_entry_flags(object, entry_index);
}
