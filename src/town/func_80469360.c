#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001E578();
extern s32 func_8001E670();
extern u8 D_8001791C[96];


typedef struct S_8001A360_0 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_8001A360_0;   /* var_s0 in func_8001A360 */

/* Process the first entry whose paired checks pass and fail, returning its index or zero. */
s32 func_8001A360(void) {
    s32 entry_index;
    u8 *entry;
    u8 *table_base;

    entry_index = 1;
    table_base = D_8001791C;
    entry = table_base + 0xC;
check_entry:
    if ((func_8001E670(((S_8001A360_0 *)entry)->unk_04) != 0) && (func_8001E670(((S_8001A360_0 *)entry)->unk_06) == 0)) {
        func_8001E578(((S_8001A360_0 *)entry)->unk_06);
        return entry_index;
    }
    entry_index += 1;
    if (entry_index < 8) {
        entry += 0xC;
        goto check_entry;
    }
    return 0;
}
