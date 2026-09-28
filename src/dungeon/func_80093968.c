#include "common.h"
#include "shared/record_ptrs.h"

extern u8 D_800DD704[];

/* Copy the current entry attribute and set damage from the item category damage table. */
void func_800990C8(u8 *entry, u8 *item) {
    entry[3] = ((u8 *) D_800814A8)[3];
    entry[0x26] = D_800DD704[item[1]];
}
