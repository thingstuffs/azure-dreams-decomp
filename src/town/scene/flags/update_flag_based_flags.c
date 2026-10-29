/* Relinked copy of town/func_80878360 (func_80878360.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene/flags.h"

extern void func_80003BCC(s32);
extern void func_80003C1C(s32);
extern s32 test_indexed_flag_treating_indices(s32);

/* Update flag 0x24C based on flags 0x20C and 0x268. */
void update_flag_based_flags(void) {
    if ((test_indexed_flag_treating_indices(0x20C) == 0) && (test_indexed_flag_treating_indices(0x268) == 0)) {
        func_80003BCC(0x24C);
        return;
    }
    func_80003C1C(0x24C);
}
