#include "common.h"

#define FIELD_U8(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern s32 func_80033B2C();
extern s32 func_800A9878(s32 arg0);
extern s32 func_800A99D8();
extern s32 func_800A9A38();
extern s32 func_800A9ADC();

extern u8 D_8006BC7A;
extern s32 *D_800D1038[];

/* Returns the table entry for a group and record, with a special-case override. */
s32 func_800A9B2C(s32 group_id, void *record) {
    s32 table_index;
    register s32 **table_slot;
    s32 **tables;
    s32 row_index;
    s32 column;
    s32 result;

    table_index = func_800A9878(group_id);
    if ((table_index != -1) && (func_800A9ADC(group_id, record) != 0)) {
        if ((FIELD_U8(record, 1) == 13) && (group_id == 9)) {
            if (FIELD_U8(record, 0) == 3) {
                if (func_80033B2C(0x12CB) != 0) {
                    u8 *special_result;

                    special_result = (u8 *)&D_8006BC7A;
                    return (s32)special_result;
                }
                return 0;
            } else {
                column = 3;
            }
        } else {
            column = func_800A9A38(record);
        }
        row_index = func_800A99D8(table_index);
        tables = D_800D1038;
        table_slot = (s32 **)((table_index * 4) + (s32)tables);
        result = (table_slot[0] + (row_index * 4))[column];
        return result;
    }
    return 0;
}
