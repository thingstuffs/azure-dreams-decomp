#include "common.h"

extern s32 func_800194E4(s32 entries, s32 entry_id);
extern void func_80019860(s16 checked_id, s16 first_id, s16 second_id);

void func_800198F4(s32 entryTable, void *resource, s32 entryKey) {
    s32 selector;
    s32 table;
    s16 *valueRecord;

    selector = *(s16 *)(entryTable + (func_800194E4(entryTable, entryKey) * 8) + 2);
    table = *(s32 *)((u8 *)resource + 0x14);
    valueRecord = (s16 *)(selector * 8 + table);
    func_80019860(valueRecord[0], valueRecord[1], valueRecord[2]);
}
