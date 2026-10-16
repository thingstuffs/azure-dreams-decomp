#include "common.h"

typedef struct FlagPair {
    u16 test_flag;
    u16 value;
} FlagPair;

extern FlagPair D_00000F10[];
extern s32 func_80000C6C(s32 flag);
extern void func_80000BC8(s32 flag);
extern void func_80000C18(s32 flag);

/* Link-at-0 devkit image copy of town/func_8087807C. */

/* Dispatch the entry's value on its test flag, then process the test flag. */
void func_80000754(s32 entry_index) {
    if (func_80000C6C(D_00000F10[entry_index].test_flag) != 0) {
        func_80000BC8(D_00000F10[entry_index].value);
    } else {
        func_80000C18(D_00000F10[entry_index].value);
    }
    func_80000BC8(D_00000F10[entry_index].test_flag);
}
