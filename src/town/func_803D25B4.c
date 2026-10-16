/* Relink of matched town/func_8032F0F4; every changed retail word is a paired relocation. */
#define townApplyEntryKeyedValues func_800195B4
#include "common.h"

extern s32 func_800191A4(void *, s32);
extern void func_80019520(s16, s16, s16);

void func_800195B4(s32 entryTable, void *resource, s32 entryKey) {
    s32 selector;
    s32 table;
    s16 *valueRecord;

    selector = *(s16 *)(entryTable + (func_800191A4(entryTable, entryKey) * 8) + 2);
    table = *(s32 *)((u8 *)resource + 0x14);
    valueRecord = (s16 *)(selector * 8 + table);
    func_80019520(valueRecord[0], valueRecord[1], valueRecord[2]);
}
