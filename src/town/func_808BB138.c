#include "common.h"
#include "m2c_compat.h"

s32 func_800007E8();                             /* extern */
M2C_UNK func_80000858();                /* extern */
M2C_UNK func_80000A38();                            /* extern */
M2C_UNK func_80000BC8();                         /* extern */
M2C_UNK func_80000C18();                         /* extern */
s32 func_80000C6C();                             /* extern */
typedef struct TownFlagEntry {
    u16 value;
    u16 pad;
} TownFlagEntry;

typedef struct TownFlagTable {
    u8 pad_00[0xF12];
    u16 flag_F12;
    u8 pad_F14[0xF28 - 0xF14];
    TownFlagEntry entry[5];
} TownFlagTable;

extern TownFlagTable D_00000000;

/* Handles triggered flags and exits after cleanup. Normal paths finalize and return index.
   The cleanup paths have no defined return value, as in the object code. */
s32 func_80000938(s32 index) {
    if ((func_80000C6C(D_00000000.flag_F12) == 0) && (func_80000C6C(0x278U) != 0)
        && (func_800007E8(index) != 0)) {
        if (func_80000C6C(0x281U) != 0) {
            func_80000C18(D_00000000.entry[2].value);
            func_80000C18(D_00000000.entry[3].value);
            func_80000C18(D_00000000.entry[4].value);
            func_80000C18(0x281U);
            func_80000C18(0x280U);
            func_80000C18(0x278U);
            func_80000A38();
            return;
        }
        if (func_80000C6C(0x288U) != 0) {
            func_80000BC8(D_00000000.entry[index].value);
            func_80000C18(0x278U);
            func_80000A38();
            return;
        }
    }
    func_80000858(index, 0);
    return index;
}

