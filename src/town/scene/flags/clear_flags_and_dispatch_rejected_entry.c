#include "common.h"
#include "town/shop/state.h"
#include "town/scene.h"
#include "town/scene/flags.h"
#include "town/devkit/flag_test_imports.h"

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

/* Finalize the index, or return the selected entry callback result after cleanup. */
s32 clear_flags_and_dispatch_rejected_entry(s32 index) {
    if ((test_linked_flag_80000c6c(D_00000000.flag_F12) == 0) && (test_linked_flag_80000c6c(0x278U) != 0)
        && (is_next_entry_zero_after_skipping(index) != 0)) {
        if (test_linked_flag_80000c6c(0x281U) != 0) {
            func_80000C18(D_00000000.entry[2].value);
            func_80000C18(D_00000000.entry[3].value);
            func_80000C18(D_00000000.entry[4].value);
            func_80000C18(0x281U);
            func_80000C18(0x280U);
            func_80000C18(0x278U);
            return dispatch_first_rejected_entry_b();
        }
        if (test_linked_flag_80000c6c(0x288U) != 0) {
            func_80000BC8(D_00000000.entry[index].value);
            func_80000C18(0x278U);
            return dispatch_first_rejected_entry_b();
        }
    }
    func_80000858(index, 0);
    return index;
}

