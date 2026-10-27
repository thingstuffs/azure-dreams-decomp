#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"

typedef struct SceneValueEntry {
    u8 pad_00[4];
    s32 value;
} SceneValueEntry;

typedef struct SceneFlagContext {
    u8 pad_00[0x18];
    s16 flag;
} SceneFlagContext;

s32 func_80017710(void *table, s32 lookup_key);

/* Look up an entry, apply the context flag, and return the entry value. */
s32 lookup_entry_apply_record_code(void *table, void *context, s32 lookup_key)
{
    SceneValueEntry *entries;
    SceneFlagContext *flag_context;
    s32 entry_index;

    entries = table;
    flag_context = context;
    entry_index = func_80017710(table, lookup_key);
    func_80018A64(flag_context->flag);
    return entries[entry_index].value;
}
