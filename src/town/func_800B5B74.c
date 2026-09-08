#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B2DA0_arg1.h"

M2C_UNK func_800B3178();            /* extern */
M2C_UNK func_800B39E4();                         /* extern */


typedef struct S_800B32D4_1 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B32D4_1;   /* temp_a1 in func_800B32D4 */

/* Prepare the linked data and update its offset 0x40 using the source record. */
void func_800B32D4(Rec_func_800B2DA0_arg1 *record) {
    void *source_record;

    func_800B39E4(record->unk_A8);
    source_record = record->unk_00;
    func_800B3178(record->unk_A8 + 0x40, source_record + 0x1C, ((S_800B32D4_1 *)source_record)->unk_3C);
}
