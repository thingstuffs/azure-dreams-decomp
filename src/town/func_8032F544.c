#include "common.h"

extern s32 townFindEntry8IndexOrAssert(s32 entries, s32 entry_id);
extern s32 townGetScriptFlagMask(s32 flagIndex);

/* Resolve a table entry to its referenced flag and query that flag. */
void townResolveEntryFlag(s32 entry_table, void *context, s32 entry_key) {
    s32 entry_index;
    s32 flag_index;
    s32 flag_table;

    entry_index = townFindEntry8IndexOrAssert(entry_table, entry_key);
    flag_index = *(s16 *)(entry_table + (entry_index * 8) + 2);
    flag_table = *(s32 *)((u8 *)context + 0x14);
    townGetScriptFlagMask(*(s16 *)(flag_table + (flag_index * 8) + 2));
}
