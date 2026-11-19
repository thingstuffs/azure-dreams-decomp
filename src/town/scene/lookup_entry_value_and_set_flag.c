#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene.h"

typedef struct SceneFlagContext {
    u8 pad_00[0x18];
    s16 flag;
} SceneFlagContext;


/* Look up an entry, apply the context flag, and return the entry value. */
s32 lookup_entry_value_and_set_flag(ScenePositionEntry *entries, SceneFlagContext *context, s32 lookup_key)
{
    s32 entry_index;

    entry_index = find_eight_byte_entry_or_assert(entries, lookup_key);
    set_script_flag_bit(context->flag);
    return entries[entry_index].result;
}
