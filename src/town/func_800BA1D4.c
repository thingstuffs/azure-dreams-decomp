#include "common.h"

extern s32 func_800B7428(s16, s16, s32);
extern s32 D_800D17D8[];

/* Apply the selected table entry at the given coordinates. */
void func_800B7934(s16 x, s16 y, u8 entry_index) {
    func_800B7428(x, y, D_800D17D8[entry_index]);
}
