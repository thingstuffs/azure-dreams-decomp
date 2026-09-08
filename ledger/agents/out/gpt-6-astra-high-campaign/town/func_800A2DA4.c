#include "common.h"
#include "m2c_compat.h"

s32 func_800A027C();                     /* extern */
void *func_800A04A8();                              /* extern */
M2C_UNK func_800A04B4();                            /* extern */

typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;   /* temp_v0 in func_800A0504 */

/* Run the follow-up action when the current record has an eligible type and passes the check. */
void func_800A0504(s32 check_value) {
    u8 record_type;
    S_800A0504_0 *record;

    record = func_800A04A8();
    record_type = record->unk_01;
    if ((record_type != 0) && (record_type != 0x13) && (func_800A027C(record, check_value) != 0)) {
        func_800A04B4();
    }
}
