#include "common.h"
#include "m2c_compat.h"

s32 func_800B0718();                                /* extern */
M2C_UNK func_800B23C0();                      /* extern */

typedef struct S_800B2B60_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    u8 pad_2C[0x10];
    u32 unk_3C;
} S_800B2B60_0;   /* arg0 in func_800B2B60 */

/* Initialize the record table pointer, stored value, and group index. */
void func_800B2B60(void *record) {
    ((S_800B2B60_0 *)record)->unk_3C = (u32 *)0x8001029C;
    ((S_800B2B60_0 *)record)->unk_28 = func_800B0718();
    func_800B23C0(record + 0x1C);
}
