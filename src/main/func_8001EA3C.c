#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001EA3C_0 {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    u8 pad_10[0x34];
    s32 unk_44;
} S_8001EA3C_0;   /* arg0 in func_8001EA3C; pointer addresses record offset 0x10 */


/* Clears flag 0x2000 and copies the record's value at offset 0x44 to offset 0x00 when set. */
void func_8001EA3C(void *record_data) {
    u16 flags;

    flags = ((S_8001EA3C_0 *)((u8 *)record_data - 0x10))->unk_0E;
    if (flags & 0x2000) {
        ((S_8001EA3C_0 *)((u8 *)record_data - 0x10))->unk_0E = (u16) (flags & 0xDFFF);
        ((S_8001EA3C_0 *)((u8 *)record_data - 0x10))->unk_00 = (s32) ((S_8001EA3C_0 *)((u8 *)record_data - 0x10))->unk_44;
    }
}
