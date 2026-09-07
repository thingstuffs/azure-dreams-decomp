#include "common.h"
#include "m2c_compat.h"

typedef struct S_8009D7D0_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_8009D7D0_0;   /* var_a0 in func_8009D7D0 */

void func_8009D7D0(s8 *arg0) {
    s8 *var_a0;

    var_a0 = arg0;
    if ((((S_8009D7D0_0 *)var_a0)->unk_01 & 0xC0) != 0x80) {
        do {
            *var_a0 = 0;
            var_a0 += 0x14;
        } while ((((S_8009D7D0_0 *)var_a0)->unk_01 & 0xC0) != 0x80);
    }
}
