#include "common.h"

#include "town/scene/entry_requests.h"
#include "town/player/script_flags.h"
#include "town/scene/flags.h"

/* Resolve a table entry to its referenced flag and query that flag. */
s32 resolve_entry_flag(void *entry_table, void *context, s32 entry_key) {
    s32 entry_index;
    s32 flag_index;
    s16 *flag_table;

    entry_index = find_entry_8_index_or_assert(entry_table, entry_key);
    flag_index = *(s16 *)(entry_table + (entry_index * 8) + 2);
    flag_table = *(s16 **)((u8 *)context + 0x14);
    return get_script_flag_mask(flag_table[flag_index * 4 + 1]);
}
