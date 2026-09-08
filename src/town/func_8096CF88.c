#include "common.h"
#include "m2c_compat.h"

/* extern */

typedef struct S_80125420_0 {
    u8 pad_00[0x4];
    u16 unk_04;
    s16 unk_06;
    u8 pad_08[0x2];
    s8 unk_0A;
} S_80125420_0;   /* arg0 in func_80125420 */


M2C_UNK func_801248C0(S_80125420_0 *);
void func_80125420(S_80125420_0 *arg0) {
    u16 temp_v0;

    temp_v0 = arg0->unk_04 + 1;
    arg0->unk_04 = temp_v0;
    if ((s16) temp_v0 == arg0->unk_06) {
        func_801248C0(arg0);
        arg0->unk_0A = 8;
        arg0->unk_06 = 0;
        arg0->unk_04 = 0U;
    }
}
