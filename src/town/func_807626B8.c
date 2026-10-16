#include "common.h"

/* Copy, in this TOWN script module, of the module-0 helper townResolveEntryFlag (src/town/func_8032F544.c);
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

extern s32 func_800165FC(ScriptEntry8 *entries, s32 entry_key);
extern s32 func_8001781C(s32 flag);

/* Resolve a table entry to its referenced flag and query that flag. */
void func_80016EB8(ScriptEntry8 *entry_table, ScriptContext *context, s32 entry_key) {
    s32 entry_index;

    entry_index = func_800165FC(entry_table, entry_key);
    func_8001781C(*(s16 *)((u8 *)context->flag_records + entry_table[entry_index].flag_index * 8 + 0x4));
}
