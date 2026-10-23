#include "common.h"

typedef struct FlagPair {
    u16 test_flag;
    u16 value;
} FlagPair;

extern FlagPair D_00003F58[];
extern s32 test_indexed_flag_treating_indices(s32 flag);
extern void func_80003BCC(s32 flag);
extern void func_80003C1C(s32 flag);

/*
 * Tests the indexed entry flag and sends its value to func_80003BCC or func_80003C1C, then sends
 * the test flag to func_80003BCC.
 *
 * Link-at-0 devkit image copy of shop_dispatch_entry_value (retail row 0x8070207C; original batch
 * key 0x8087807C).
 */
void dispatch_entry_test_flag_test(s32 entry_index) {
    if (test_indexed_flag_treating_indices(D_00003F58[entry_index].test_flag) != 0) {
        func_80003BCC(D_00003F58[entry_index].value);
    } else {
        func_80003C1C(D_00003F58[entry_index].value);
    }
    func_80003BCC(D_00003F58[entry_index].test_flag);
}
