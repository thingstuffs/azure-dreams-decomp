#include "common.h"

void clear_indexed_flag_bit(s32 flag_id);
extern u8 devkit_flag_ids[];

/* Pass the indexed table value to clear_indexed_flag_bit. */
void pass_indexed_devkit_value(s32 index) {
    clear_indexed_flag_bit(*(s16 *)(devkit_flag_ids + (index * 2)));
}

/* MECHANISM: Preserve the seed's 0x18 RA-only frame and direct call shape.
   Naming the literal table base D_80700BB4 selects the symbol+index lh macro,
   whose $at-first address add matches retail's commutative operand order. */
