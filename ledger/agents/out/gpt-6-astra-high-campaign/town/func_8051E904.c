#include "common.h"
#include "m2c_compat.h"

typedef struct S_8051E904_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8051E904_1;   /* ((temp_s0 * 8) + arg0) in func_8051E904 */




extern s32 func_80017710(s32, M2C_UNK);
extern M2C_UNK func_80018A64();

typedef struct S_8051E904_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8051E904_0;   /* arg1 in func_8051E904 */

/* Look up an entry, apply the record code, and return the entry value. */
s32 func_8051E904(s32 table_base, S_8051E904_0 *record, M2C_UNK lookup_key) {
    s32 entry_index;

    entry_index = func_80017710(table_base, lookup_key);
    func_80018A64(record->unk_18);
    return ((S_8051E904_1 *)(((entry_index * 8) + table_base)))->unk_04;
}
