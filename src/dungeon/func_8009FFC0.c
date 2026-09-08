#include "common.h"

extern s32 func_800353F4(s8 *arg0);
extern u16 D_80013714;

typedef struct S_800A5720_0 {
    u8 unk_00;
    u8 unk_01;
} S_800A5720_0;   /* var_a1 in func_800A5720 */

s32 func_800A5720(s8 *arg0) {
    s8 *var_a1;
    u8 temp_v1;

    if (!(D_80013714 & 2)) {
        var_a1 = arg0;
        if (*arg0 > 0) {
            do {
                var_a1 += 1;
            } while (*var_a1 > 0);
        }
        if (((S_800A5720_0 *)var_a1)->unk_00 == 0x82) {
            temp_v1 = ((S_800A5720_0 *)var_a1)->unk_01;
            if ((u32) ((temp_v1 + 0x7F) & 0xFF) < 0x1AU) {
                ((S_800A5720_0 *)var_a1)->unk_01 = (u8) (temp_v1 - 0x21);
            }
        }
        return func_800353F4(arg0);
    }
    return 0;
}
