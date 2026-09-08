#include "common.h"

extern s32 func_800194E4(s32 arg0, s32 arg1);
extern s32 func_8001ADE0(s32 arg0);

/* Resolve a table entry to its referenced flag and query that flag. */
void func_80019D44(s32 entry_table, void *context, s32 entry_key) {
    s32 entry_index;
    s16 flag_index;
    s32 flag_table;

    entry_index = func_800194E4(entry_table, entry_key);
    flag_index = *(s16 *)(entry_table + (entry_index * 8) + 2);
    flag_table = *(s32 *)((u8 *)context + 0x14);
    func_8001ADE0(*(s16 *)(flag_table + (flag_index * 8) + 2));
}
