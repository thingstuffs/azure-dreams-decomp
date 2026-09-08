#include "common.h"

extern s32 func_800194E4(s32 arg0, s32 arg1);
extern void func_80019860(s32 arg0, s32 arg1, s32 arg2);

// Passes the selected value record's three components to func_80019860.
void func_800198F4(s32 entryTable, void *resource, s32 entryKey) {
    void *valueRecord;

    valueRecord = (void *)((*(s16 *)(entryTable + (func_800194E4(entryTable, entryKey) * 8) + 2) * 8) + *(s32 *)((u8 *)resource + 0x14));
    func_80019860(*(s16 *)((u8 *)valueRecord + 0), *(s16 *)((u8 *)valueRecord + 2), *(s16 *)((u8 *)valueRecord + 4));
}
