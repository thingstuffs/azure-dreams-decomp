#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800B2FF8();            /* extern */

typedef struct S_800B30D8_0 {
    void * unk_00;
    u8 pad_04[0xA4];
    s32 unk_A8;
} S_800B30D8_0;   /* arg0 in func_800B30D8 */

typedef struct S_800B30D8_1 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B30D8_1;   /* temp_a1 in func_800B30D8 */

/* Update the linked data at offset 0x18 using the source record. */
void func_800B30D8(S_800B30D8_0 *record) {
    void *source_record;

    source_record = record->unk_00;
    func_800B2FF8(record->unk_A8 + 0x18, source_record + 0x1C, ((S_800B30D8_1 *)source_record)->unk_3C);
}
