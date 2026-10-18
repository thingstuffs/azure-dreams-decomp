#include "common.h"

typedef struct FlagPair {
    u16 test_flag;
    u16 value;
} FlagPair;

extern FlagPair D_00003F58[];
extern s32 test_indexed_flag_treating_indices(s32 flag);
extern void func_80003BCC(s32 flag);
extern void func_80003C1C(s32 flag);

/* Link-at-0 devkit image copy of town/func_8087807C. */

/* Dispatch the entry's value on its test flag, then process the test flag. */
void dispatch_entry_test_flag_test(s32 entry_index) {
    if (test_indexed_flag_treating_indices(D_00003F58[entry_index].test_flag) != 0) {
        func_80003BCC(D_00003F58[entry_index].value);
    } else {
        func_80003C1C(D_00003F58[entry_index].value);
    }
    func_80003BCC(D_00003F58[entry_index].test_flag);
}
