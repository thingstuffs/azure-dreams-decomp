#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

/* Look up an entry, apply the context flag, and return the entry value. */
s32 lookup_entry_value_and_set_flag(ScenePositionEntry *entries, TownObjectSet *context, s32 lookup_key)
{
    s32 entry_index;

    entry_index = find_eight_byte_entry_or_assert(entries, lookup_key);
    set_script_flag_bit(context->entry_flag);
    return entries[entry_index].result;
}
