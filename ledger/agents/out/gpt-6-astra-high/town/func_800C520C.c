#include "common.h"

extern u8 D_800D4FB8;

/* Returns the address of the indexed 24-byte entry. */
void *func_800C296C(s32 entry_index) {
    return (entry_index * 0x18) + &D_800D4FB8;
}
