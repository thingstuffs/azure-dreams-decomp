#include "town/scene.h"
#include "town/player/script_flags.h"
#include "town/scene/record_actions.h"
#include "town/scene/flags.h"


/* Set the indexed entry flag while the fixed script flag is enabled. */
s32 set_indexed_entry_flag_if_dac(void *object, s32 entry_index)
{
    if (get_script_flag_mask(0xDAC) != 0) {
        set_indexed_entry_flag(object, entry_index);
        return 1;
    }
    return 0;
}
