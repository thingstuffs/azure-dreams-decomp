/* Relinked copy of town/func_80878314 (func_80878314.c); the selected-flag operand is spelled as the symbol it is (the twin spells the address as a literal), otherwise retail differs only at relocation sites. */
#include "common.h"

extern u16 D_00003F5A[];

s32 test_indexed_flag_treating_indices();                             /* extern */

/* Return 2 when the selected flag is set and flag 0x1F9 is clear. */
s32 get_2_flag_flag(void) {
    s32 result;

    result = 0;
    if (test_indexed_flag_treating_indices(D_00003F5A[0]) != 0) {
        result = (test_indexed_flag_treating_indices(0x1F9U) == 0) * 2;
    }
    return result;
}
