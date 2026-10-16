#include "common.h"

typedef struct {
    s16 unk0;
    s16 selector;
    s32 result;
} Entry;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
} Position;

extern s32 townFindEntry8IndexOrAssert();
extern void townUpdateDependentEntryIds();
extern s32 townAllEntriesPassCheck();
extern void townSetScriptFlagBit();

/* Applies the selected entry's position and returns its result. */
s32 townApplyEntryPosition(Entry *entries, s32 object, void *context, s32 selection)
{
    s32 saved_object;
    s32 entry_index;
    Position *position;
    s32 selector;
    s32 table;

    saved_object = object;

    entry_index = townFindEntry8IndexOrAssert(entries, selection);
    selector = entries[entry_index].selector;
    table = *(s32 *)((u8 *)context + 0x14);
    position = (Position *)(selector * 8 + table);
    townUpdateDependentEntryIds(position->x, position->y, position->z);

    if (saved_object != 0 && townAllEntriesPassCheck(saved_object) != 0) {
        townSetScriptFlagBit(*(s16 *)((u8 *)context + 0x18));
    }

    return entries[entry_index].result;
}
