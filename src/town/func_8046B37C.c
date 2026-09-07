#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_8001E950.h"



s32 func_8001E670();                             /* extern */
extern s16 D_8001792C;
extern Rec_D_8001E950 *D_8001E950;

s32 func_8001C37C(void) {
    s32 var_a0;

    var_a0 = 0;
    if (D_8001E950->unk_04 != 1) {
        var_a0 = func_8001E670(D_8001792C) != 0;
    }
    return var_a0;
}
