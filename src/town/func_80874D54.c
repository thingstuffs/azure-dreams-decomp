/* Relinked copy of town/func_80874D24 (func_80874D24.c); retail differs only at relocation sites. */
#include "common.h"

void func_80701808();                         /* extern */
extern u8 D_80700BB4[];

/* Pass the indexed table value to func_80701808. */
void func_80700D54(s32 index) {
    func_80701808(*(s16 *)(D_80700BB4 + (index * 2)));
}

/* MECHANISM: Preserve the seed's 0x18 RA-only frame and direct call shape.
   Naming the literal table base D_80700BB4 selects the symbol+index lh macro,
   whose $at-first address add matches retail's commutative operand order. */
