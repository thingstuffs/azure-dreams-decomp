#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B384C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    u8 pad_14[0x14];
    s32 unk_28;
} S_800B384C_0;   /* arg0 in func_800B384C; pointer addresses record offset 0x10 */


extern M2C_UNK D_800B34FC;

/* Set the record's base and offset values and its data pointer. */
void func_800B384C(void *record_field, s32 base_value) {
    ((S_800B384C_0 *)((u8 *)record_field - 0x10))->unk_28 = base_value;
    ((S_800B384C_0 *)((u8 *)record_field - 0x10))->unk_10 = (s32) (base_value + 0x20);
    ((S_800B384C_0 *)((u8 *)record_field - 0x10))->unk_00 = &D_800B34FC;
}
