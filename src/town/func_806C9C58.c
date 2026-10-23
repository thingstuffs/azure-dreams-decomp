#include "common.h"
#include "town/scene/entry_flag_queries.h"

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

extern s32 func_8001639C(ScriptEntry8 *entries, s32 entry_key);
extern s32 func_800175BC(s32 flag);

/* Resolve a table entry to its referenced flag and query that flag. */
void query_scene_entry_flag_k(ScriptEntry8 *entries, ScriptContext *context, s32 entry_key) {
    s32 entry_index;

    entry_index = func_8001639C(entries, entry_key);
    func_800175BC(*(s16 *)((u8 *)context->flag_records + entries[entry_index].flag_index * 8 + 0x4));
}
