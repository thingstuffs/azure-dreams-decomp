#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016DE0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80016DE0_1;   /* temp_v1 in func_80016DE0 */


extern Rec_D_80016000 *D_80016000;

/* Scale the linked record's value by 64 and add 0x220. */
void func_80016DE0(void) {
    S_80016DE0_1 *record;

    record = D_80016000->unk_1C.as_pv;
    record->unk_04 = (s32) ((record->unk_04 << 6) + 0x220);
}
