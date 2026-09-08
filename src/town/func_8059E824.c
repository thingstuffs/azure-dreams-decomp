#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_80016824_1 {
    u8 pad_00[0x7];
    u8 unk_07;
} S_80016824_1;   /* temp_v1 in func_80016824 */


M2C_UNK func_8001886C();                     /* extern */
extern Rec_D_80016000 *D_80016000;

/* Decrement the countdown and invoke handler 0x5FF when it reaches zero. */
void func_80016824(void) {
    u8 countdown;
    S_80016824_1 *countdown_record;

    countdown_record = D_80016000->unk_40.as_s32 + 0x68;
    countdown = countdown_record->unk_07 - 1;
    countdown_record->unk_07 = countdown;
    if (!(countdown & 0xFF)) {
        func_8001886C(0x5FF);
    }
}
