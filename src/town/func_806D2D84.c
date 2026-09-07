#include "common.h"
#include "m2c_compat.h"

s32 func_80016D78();                             /* extern */
extern s16 D_800160B2;

typedef struct S_80016584_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016584_0;   /* arg0 in func_80016584 */

s32 func_80016584(S_80016584_0 *arg0) {
    s32 var_v0;

    var_v0 = 0;
    if (func_80016D78(D_800160B2) == 0) {
        var_v0 = func_80016D78(arg0->unk_18) != 0;
    }
    return var_v0;
}
