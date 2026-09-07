#include "common.h"
#include "m2c_compat.h"

s32 func_8008FE90();                                /* extern */

typedef struct S_80095910_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80095910_0;   /* arg0 in func_80095910 */

void func_80095910(S_80095910_0 *arg0) {
    arg0->unk_10 = func_8008FE90();
}
