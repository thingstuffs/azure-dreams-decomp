#include "modules/town_town_windows.h"

// Processes the selected town record and saves the returned result.
s32 get_window_mode_value(void)
{
    func_800A0C10_TownRecord *townRecords = (func_800A0C10_TownRecord *)0x80010AB4;
    s32 selectedRecordIndex = D_800CFCC4->unk_4F & 0x3F;

    D_80100AF0 = func_8004B854(
        0,
        townRecords[selectedRecordIndex].bytes,
        ((func_800A0C10_TownPage *)0x80010000)->entries[selectedRecordIndex].value);
    return 0;
}
