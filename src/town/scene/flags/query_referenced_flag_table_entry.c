#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene/flags.h"
#include "town/player/state.h"
#include "town/scene.h"

/* Copy, in this TOWN script module, of the module-0 helper resolve_entry_flag (src/town/func_8032F544.c);
 * this build reads the flag number from offset 0x4 of the flag record. */

typedef struct ScriptFlagRecord {
    u8 pad_00[0x4];
    s16 flag;
    u8 pad_06[2];
} ScriptFlagRecord;

typedef struct ScriptContext {
    u8 pad_00[0x14];
    ScriptFlagRecord *flag_records;
} ScriptContext;

/* Resolve a table entry to its referenced flag and return that flag's query result. */
s32 query_referenced_flag_for_table_entry(ScenePositionEntry *entry_table, ScriptContext *context, s32 entry_key) {
    s32 entry_index;

    entry_index = find_eight_byte_entry_or_assert(entry_table, entry_key);
    return get_script_flag_mask(context->flag_records[entry_table[entry_index].selector].flag);
}
