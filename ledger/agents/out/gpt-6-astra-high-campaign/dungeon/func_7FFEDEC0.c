#include "common.h"

extern s32 D_800CFBA0[];
void func_8008B5D8(s32, s32);

/* Submits the indexed table value with command 0x23. */
void func_8008B620(s32 entry_index) {
    func_8008B5D8(D_800CFBA0[entry_index], 0x23);
}
