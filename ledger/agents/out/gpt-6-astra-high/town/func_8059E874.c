#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016874_1 {
    u8 pad_00[0x7];
    u8 unk_07;
} S_80016874_1;   /* temp_v1 in func_80016874 */


extern Rec_D_80016000 *D_80016000;

/* Increment the byte counter in the record at offset 0x68. */
void func_80016874(void) {
    S_80016874_1 *counter_record;

    counter_record = D_80016000->unk_40.as_s32 + 0x68;
    counter_record->unk_07 = (u8) (counter_record->unk_07 + 1);
}
