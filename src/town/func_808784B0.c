#include "common.h"

extern s32 D_80700000[];
extern s32 D_80701DC4[];

extern void devReportKindModeSno(s32 kind);
extern void townShopSetEntryStepFlag(s32 index, s32 entry_index);

/* Read the selected row value and process entry 3 before returning it. */
s32 townShopReadSelectedRowValue(void) {
    s32 row_index;
    s32 row_value;

    row_index = D_80701DC4[0];
    row_value = *(s32 *)((u8 *)D_80700000 + (row_index << 5) + 0x1E40);
    townShopSetEntryStepFlag(row_index, 3);
    devReportKindModeSno(3);
    return row_value;
}
