#include "common.h"
#include "m2c_compat.h"

s32 func_80016D78();                             /* extern */
extern s16 D_800160B2;

typedef struct S_80016584_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016584_0;   /* arg0 in func_80016584 */

/* Check the record flag only when the global flag is clear. */
s32 func_80016584(S_80016584_0 *record) {
    s32 flag_set;

    flag_set = 0;
    if (func_80016D78(D_800160B2) == 0) {
        flag_set = func_80016D78(record->unk_18) != 0;
    }
    return flag_set;
}
