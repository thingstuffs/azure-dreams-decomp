#include "common.h"
#include "m2c_compat.h"

s32 func_8002190C();                                /* extern */

typedef struct S_80027A68_0 {
    s32 unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80027A68_0;   /* arg0 in func_80027A68 */

/* Store the supplied field values and capture the helper result. */
void func_80027A68(S_80027A68_0 *record, s32 value_14, s32 value_00) {
    record->unk_14 = value_14;
    record->unk_00 = value_00;
    record->unk_0C = func_8002190C();
}
