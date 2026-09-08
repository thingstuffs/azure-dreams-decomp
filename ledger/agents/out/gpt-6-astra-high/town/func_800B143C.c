#include "common.h"

extern void func_800491F4(s32, void *, s32);
extern u8 D_800D1594[];

/* Link entries in D_800D1594 order until an index reaches 26. */
void func_800AEB9C(s32 entries) {
    func_800491F4(entries, D_800D1594, 26);
}
