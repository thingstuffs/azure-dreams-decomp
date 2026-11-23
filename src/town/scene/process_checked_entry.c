#include "common.h"
#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene.h"


// Processes the selected entry if the object's handle passes its status check.
s32 process_checked_entry(TownObjectSet *object, s32 entryIndex)
{
    s32 processed;

    if (get_script_flag_mask(object->entry_flag) == 0) {
        processed = 0;
    } else {
        set_script_flag_bit(object->choices[entryIndex].script_flag);
        clear_script_flag_bit(object->entry_flag);
        processed = 1;
    }
    return processed;
}
