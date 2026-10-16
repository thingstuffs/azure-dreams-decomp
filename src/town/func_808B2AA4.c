/* Relinked copy of town/func_80874D24 (func_80874D24.c); retail differs only at relocation sites. */
#include "common.h"

void func_80700D6C();                         /* extern */
extern u8 D_A0700F2C[];

/* Pass the indexed table value to func_80700D6C. */
void func_807002A4(s32 index) {
    func_80700D6C(*(s16 *)(D_A0700F2C + (index * 2)));
}

/* MECHANISM: Preserve the seed's 0x18 RA-only frame and direct call shape.
   Naming the literal table base D_A0700F2C selects the symbol+index lh macro,
   whose $at-first address add matches retail's commutative operand order. */
