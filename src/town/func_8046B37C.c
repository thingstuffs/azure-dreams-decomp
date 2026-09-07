#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001C37C_0 {
    u8 pad_00[0x4];
    u8 unk_04;
} S_8001C37C_0;   /* D_8001E950 in func_8001C37C */


s32 func_8001E670();                             /* extern */
extern s16 D_8001792C;
extern S_8001C37C_0 *D_8001E950;

s32 func_8001C37C(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_8001E950->unk_04 != 1) {
        var_a0 = func_8001E670(D_8001792C) != 0;
    }
    return var_a0;
}
