#include "common.h"
#include "m2c_compat.h"

s16 func_800BCB04();                   /* extern */

typedef struct S_800BCAD0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BCAD0_0;   /* arg0 in func_800BCAD0 */

s16 func_800BCAD0(S_800BCAD0_0 *arg0) {
    return func_800BCB04(arg0->unk_02, arg0->unk_06, arg0->unk_0A);
}
