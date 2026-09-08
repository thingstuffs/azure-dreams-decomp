#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80019A34_2 {
    u8 pad_00[0x74];
    void * (*unk_74)(M2C_UNK);
} S_80019A34_2;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_80019A34 */


typedef struct S_80019A34_0 {
    u8 unk_00;
    u8 unk_01;
} S_80019A34_0;   /* temp_v0 in func_80019A34 */

typedef struct {
    u8 unk0;
    u8 unk1;
} FuncData;

extern void *D_80016000;

/* Checks whether the callback's record matches the two expected bytes. */
s32 func_80019A34(s32 expected_second, s32 expected_first) {
    S_80019A34_0 *record;

    record = ((S_80019A34_2 *)(((Rec_D_80016000 *)D_80016000)->unk_20))->unk_74(0);
    if (record == NULL) {
        return 0;
    } else {
        return record->unk_01 == expected_second &&
               record->unk_00 == expected_first;
    }
}
