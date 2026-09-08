#include "common.h"
#include "m2c_compat.h"

extern u8 D_80011F80[];
asm(".globl D_80011F80\nD_80011F80 = 0x80011F80");

typedef struct S_800B2964_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2964_0;   /* var_v1 in func_800B2964 */

/* Collect pointers to enabled entries and terminate the list with NULL. */
void func_800B2964(M2C_UNK *entries, s32 entry_count) {
    M2C_UNK *output;
    s8 *entry;
    s32 entry_index;

    output = entries;
    entry_index = 0;
    if (entry_count > 0) {
        entry = D_80011F80;
        do {
            if (((S_800B2964_0 *)entry)->unk_01 != 0) {
                *output = (M2C_UNK) entry;
                output += 1;
            }
            entry_index += 1;
            entry += 4;
        } while (entry_index < entry_count);
    }
    *output = NULL;
}
