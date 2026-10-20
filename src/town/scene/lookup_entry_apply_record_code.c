#include "common.h"

typedef struct S_8051E904_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8051E904_1;
s32 func_80017710(s32, s32);
void func_80018A64(s32);

typedef struct S_8051E904_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8051E904_0;   /* arg1 in lookup_entry_apply_record_code */

/* Look up an entry, apply the record code, and return the entry value. */
s32 lookup_entry_apply_record_code(s32 table_base, S_8051E904_0 *record, s32 lookup_key) {
    s32 entry_index;

    entry_index = func_80017710(table_base, lookup_key);
    func_80018A64(record->unk_18);
    return ((S_8051E904_1 *)(((entry_index * 8) + table_base)))->unk_04;
}
