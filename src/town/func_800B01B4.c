#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AD914_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800AD914_0;   /* arg0 in func_800AD914 */

typedef struct S_800AD914_1 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_800AD914_1;   /* var_a0 in func_800AD914 */

/* Count entries with flag 0x20, excluding IDs 0x17 and 0x18. */
s32 func_800AD914(void *entries) {
    s32 count;
    u8 *entry_id_ptr;
    u8 entry_id;

    entry_id = ((S_800AD914_0 *)entries)->unk_01;
    count = 0;
    if (entry_id != 0) {
        entry_id_ptr = entries + 1;
        do {
            if ((((S_800AD914_1 *)entry_id_ptr)->unk_02 & 0x20) && ((u32) (entry_id - 0x17) >= 2U)) {
                count += 1;
            }
            entry_id_ptr += 4;
            entry_id = *entry_id_ptr;
        } while (entry_id != 0);
    }
    return count;
}
