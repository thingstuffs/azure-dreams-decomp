#include "common.h"

extern s32 D_80700000[];
extern s32 D_80701DC4[];

extern void func_80701FEC(s32 arg0);
extern void func_80702180(s32 index, s32 arg1);

/* Read the selected row value and process entry 3 before returning it. */
s32 func_807024B0(void) {
    s32 row_index;
    s32 row_value;

    row_index = D_80701DC4[0];
    row_value = *(s32 *)((u8 *)D_80700000 + (row_index << 5) + 0x1E40);
    func_80702180(row_index, 3);
    func_80701FEC(3);
    return row_value;
}
