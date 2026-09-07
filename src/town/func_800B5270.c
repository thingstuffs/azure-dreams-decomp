#include "common.h"
#include "m2c_compat.h"

s32 func_8004B404();                         /* extern */
M2C_UNK func_800B23C0();                      /* extern */
s32 func_800B2918();                                /* extern */
M2C_UNK func_800B2964();                    /* extern */
s32 func_800B29A4();                             /* extern */

typedef struct S_800B29D0_0 {
    u8 pad_00[0x38];
    s32 unk_38;
    u8 pad_3C[0x4];
    s32 unk_40;
    s32 unk_44;
} S_800B29D0_0;   /* arg0 in func_800B29D0 */

s32 func_800B29D0(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = func_8004B404(0x100);
    ((S_800B29D0_0 *)arg0)->unk_40 = temp_v0;
    if (temp_v0 != 0) {
        temp_v0_2 = func_800B2918();
        ((S_800B29D0_0 *)arg0)->unk_44 = temp_v0_2;
        func_800B2964(((S_800B29D0_0 *)arg0)->unk_40, temp_v0_2);
        ((S_800B29D0_0 *)arg0)->unk_38 = func_800B29A4(((S_800B29D0_0 *)arg0)->unk_40);
        func_800B23C0(arg0 + 0x2C);
    }
    return ((S_800B29D0_0 *)arg0)->unk_40;
}
