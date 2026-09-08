#include "common.h"
#include "m2c_compat.h"

extern M2C_UNK *D_800718B0[];
extern u8 D_80082E78;
extern M2C_UNK D_800D1D1C;
extern M2C_UNK D_800D1D24;
extern M2C_UNK D_800D1D2C;

/* Build a null-terminated list with one or three entries for the current event. */
void func_800B94A8(void) {
    M2C_UNK **entries;
    s32 entry_count;

    entries = D_800718B0;
    entries[0] = &D_800D1D1C;
    entry_count = 1;
    if (D_80082E78 != 0x17) {
        entry_count = 3;
        entries[1] = &D_800D1D24;
        entries[2] = &D_800D1D2C;
    }
    entries[entry_count] = NULL;
}
