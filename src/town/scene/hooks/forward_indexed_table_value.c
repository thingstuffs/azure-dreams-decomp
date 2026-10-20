/* Relinked copy of town/func_80874D24 (func_80874D24.c); retail differs only at relocation sites. */
#include "common.h"

void clear_indexed_flag_bit_unless_index_one();                         /* extern */
extern u8 D_A0700F2C[];

/* Pass the indexed table value to clear_indexed_flag_bit_unless_index_one. */
void forward_indexed_table_value(s32 index) {
    clear_indexed_flag_bit_unless_index_one(*(s16 *)(D_A0700F2C + (index * 2)));
}

/* MECHANISM: Preserve the seed's 0x18 RA-only frame and direct call shape.
   Naming the literal table base D_A0700F2C selects the symbol+index lh macro,
   whose $at-first address add matches retail's commutative operand order. */
