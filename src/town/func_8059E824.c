#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016824_1 {
    u8 pad_00[0x7];
    u8 unk_07;
} S_80016824_1;   /* temp_v1 in func_80016824 */


M2C_UNK func_8001886C();                     /* extern */
extern Rec_D_80016000 *D_80016000;

void func_80016824(void) {
    u8 temp_v0;
    S_80016824_1 *temp_v1;

    temp_v1 = D_80016000->unk_40.as_s32 + 0x68;
    temp_v0 = temp_v1->unk_07 - 1;
    temp_v1->unk_07 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        func_8001886C(0x5FF);
    }
}
