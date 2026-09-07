#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B4648_1 {
    u8 pad_00[0x18];
    s32 * unk_18;
    u8 pad_1C[0x2C];
    s32 * unk_48;
} S_800B4648_1;   /* (temp_s0 + arg0->unk_5C) in func_800B4648 */


M2C_UNK func_8004E99C();                         /* extern */

typedef struct S_800B4648_0 {
    u8 pad_00[0x5C];
    s32 unk_5C;
} S_800B4648_0;   /* arg0 in func_800B4648 */

/* Passes each of five paired entry values to func_8004E99C. */
void func_800B4648(S_800B4648_0 *owner) {
    s32 entry_value;
    s32 entry_offset;
    s32 entry_index;

    entry_index = 0;
    do {
        entry_offset = entry_index * 4;
        entry_value = *((S_800B4648_1 *)((entry_offset + owner->unk_5C)))->unk_18;
        entry_index += 1;
        func_8004E99C(entry_value);
        func_8004E99C(*((S_800B4648_1 *)((entry_offset + owner->unk_5C)))->unk_48);
    } while (entry_index < 5);
}
