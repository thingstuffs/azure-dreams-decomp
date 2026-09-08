#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016E38_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80016E38_1;   /* temp_v1 in func_80016E38 */


extern Rec_D_80016000 *D_80016000;

/* Adds 0x20 to the linked record's unk_04 value. */
void func_80016E38(void) {
    S_80016E38_1 *linked_record;

    linked_record = D_80016000->unk_1C.as_pv;
    linked_record->unk_04 = (s32) (linked_record->unk_04 + 0x20);
}
