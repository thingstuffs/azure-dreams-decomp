#include "common.h"
#include "m2c_compat.h"

extern u8 D_800EA000[];

typedef struct S_8001744C_0 {
    s16 unk_00;
} S_8001744C_0;   /* var_v0 in func_8001744C */

typedef struct S_8001744C_1 {
    s16 unk_00;
    s16 unk_02;
} S_8001744C_1;   /* var_v1 in func_8001744C */

/* Clear all three halfwords in each of the 4096 table entries. */
void func_8001744C(void) {
    s8 *entry_start;
    s8 *entry_tail;
    s32 entries_left;

    entry_start = D_800EA000;
    entries_left = 0x1000;
    entry_tail = entry_start + 2;
    do {
        entries_left -= 1;
        ((S_8001744C_0 *)entry_start)->unk_00 = 0;
        ((S_8001744C_1 *)entry_tail)->unk_02 = 0;
        ((S_8001744C_1 *)entry_tail)->unk_00 = 0;
        entry_tail += 6;
        entry_start += 6;
    } while (entries_left > 0);
}
