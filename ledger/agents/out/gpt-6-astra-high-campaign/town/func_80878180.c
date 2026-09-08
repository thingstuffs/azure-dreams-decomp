#include "common.h"

extern u8 D_80701E2C[];
extern void func_80702670(s32);

/* Set flag 0x1F9 when the selected entry has bit 0 set. */
void func_80702180(s32 row_index, s32 entry_index) {
    s32 offset;

    offset = (entry_index * 8) + (row_index << 5);
    if (*(s32 *) &D_80701E2C[offset] & 1) {
        func_80702670(0x1F9);
    }
}
