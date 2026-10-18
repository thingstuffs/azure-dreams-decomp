#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
extern void *get_special_data_for_low_value_id(s32);
extern s32 func_800178A8(void *, s32, s32);
extern void *func_80017960(void *, void *, s32, s32);
extern u8 D_80018A04[], D_80018B98[], D_8001ADCA[];

void *lookup_entry_with_special_data_override(s32 entry_id, s32 unused, s32 entry_type)
{
    void *result;
    u8 *entry_table;

    result = get_special_data_for_low_value_id(entry_type);
    if (result != 0) {
        return result;
    }

    entry_table = D_80018A04;
    result = func_80017960(entry_table, D_80018B98, entry_id, entry_type);
    if ((entry_type == 0xB) && (func_800178A8(entry_table, entry_id, 0xB) != 0)) {
        return D_8001ADCA;
    }
    return result;
}

