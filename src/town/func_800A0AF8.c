#include "modules/town_town_windows.h"

// Populate three global slots with a signed byte, lookup value, and record pointer from the first entry.
s32 townGetSelectedTableEntry(void) {
    D_80082A38[0x12] = (s8)D_800CFCC4->value;
    D_80082A38[0x13] = D_800D0910[D_800CFCC4->kind];
    D_80082A38[0x14] =
        (u32)((u8 *)0x80010AB4 +
              ((D_800CFCC4->unk_4F & 0x3F) * 0x54));
    return 0;
}
