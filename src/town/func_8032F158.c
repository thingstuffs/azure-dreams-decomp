#include "common.h"
#include "m2c_compat.h"

void set_script_flag_bit();                 /* extern */

typedef struct S_80019958_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80019958_0;   /* arg0 in set_indexed_entry_flag */

typedef struct S_80019958_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
} S_80019958_1;

/* Set the indexed entry flag using its identifier and entry pointer. */
void set_indexed_entry_flag(S_80019958_0 *record, s32 entry_index) {
    set_script_flag_bit(((S_80019958_1 *)(record->unk_10 + entry_index * 0x10))->unk_0C);
}
