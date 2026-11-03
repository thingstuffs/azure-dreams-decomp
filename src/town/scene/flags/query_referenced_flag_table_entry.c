#include "common.h"
#include "town/scene/flags.h"

/* Copy, in this TOWN script module, of the module-0 helper resolve_entry_flag (src/town/func_8032F544.c);
 * this build reads the flag number from offset 0x4 of the flag record. */

typedef struct ScriptEntry8 {
    s16 unk_00;
    s16 flag_index;
    s16 unk_04;
    s16 unk_06;
} ScriptEntry8;

typedef struct ScriptFlagRecord {
    u8 pad_00[0x4];
    s16 flag;
} ScriptFlagRecord;

typedef struct ScriptContext {
    u8 pad_00[0x14];
    ScriptFlagRecord *flag_records;
} ScriptContext;

extern s32 find_entry_8_index_or_assert(ScriptEntry8 *entries, s32 entry_key);
extern s32 get_script_flag_mask(s32 flag);

/* Resolve a table entry to its referenced flag and return that flag's query result. */
s32 query_referenced_flag_for_table_entry(ScriptEntry8 *entry_table, ScriptContext *context, s32 entry_key) {
    s32 entry_index;

    entry_index = find_entry_8_index_or_assert(entry_table, entry_key);
    return get_script_flag_mask(*(s16 *)((u8 *)context->flag_records + entry_table[entry_index].flag_index * 8 + 0x4));
}
