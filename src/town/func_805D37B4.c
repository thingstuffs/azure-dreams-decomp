#include "common.h"
#include "m2c_compat.h"

extern u8 D_800198A4[];
extern s32 D_80019B8C;

typedef struct S_805D37B4_0 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_805D37B4_0;   /* base + offset in func_805D37B4 */

/* Returns the field at offset 0x04 of the selected 0x18-byte table entry. */
s32 func_805D37B4(void) {
    s32 entry_offset;
    u8 *table_base;

    table_base = D_800198A4;
    entry_offset = D_80019B8C * 0x18;
    return ((S_805D37B4_0 *)(table_base + entry_offset))->unk_04;
}
