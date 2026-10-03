#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"



typedef struct S_80019A34_0 {
    u8 unk_00;
    u8 unk_01;
} S_80019A34_0;   /* temp_v0 in func_80019A34 */


/* Checks whether the callback's record matches the two expected bytes. */
s32 func_80019A34(s32 expected_second, s32 expected_first) {
    S_80019A34_0 *record;

    record = D_80016000->unk_20->callback_074(0);
    if (record == NULL) {
        return 0;
    } else {
        return record->unk_01 == expected_second &&
               record->unk_00 == expected_first;
    }
}
