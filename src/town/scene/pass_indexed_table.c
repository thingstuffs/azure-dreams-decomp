/* Relinked copy of town/func_80874D24 (func_80874D24.c); retail differs only at relocation sites. */
#include "common.h"
#include "town/scene/flags.h"
#include "town/scene.h"

extern u8 devkit_flag_ids[];

/* Pass the indexed table value to set_indexed_flag_bit. */
void pass_indexed_table(s32 index) {
    set_indexed_flag_bit(*(s16 *)(devkit_flag_ids + (index * 2)));
}

/* MECHANISM: Preserve the seed's 0x18 RA-only frame and direct call shape.
   Naming the literal table base D_80700BB4 selects the symbol+index lh macro,
   whose $at-first address add matches retail's commutative operand order. */
