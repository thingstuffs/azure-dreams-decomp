#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8059E700_1 {
    u8 pad_00[0x2D5C];
    s32 unk_2D5C;
} S_8059E700_1;   /* record in func_8059E700 */


extern Rec_D_80016000 *D_80016000;

/* Subtracts an amount from the record's value at offset 0x2D5C. */
void func_8059E700(s32 amount) {
    S_8059E700_1 *record;

    record = D_80016000->unk_38.as_pv;
    record->unk_2D5C = (s32) (record->unk_2D5C - amount);
}
