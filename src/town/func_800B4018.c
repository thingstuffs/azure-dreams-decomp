#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B0FD4();                      /* extern */
M2C_UNK func_800B173C();                      /* extern */

typedef struct S_800B1778_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_800B1778_0;   /* temp_s0 in func_800B1778 */

/* Set two subrecord values and run their associated update routines. */
void func_800B1778(s32 record_address, s32 value_10, s32 value_08) {
    S_800B1778_0 *subrecord;

    subrecord = record_address + 0x20;
    subrecord->unk_08 = value_08;
    func_800B173C(subrecord);
    subrecord->unk_10 = value_10;
    func_800B0FD4(subrecord);
}
