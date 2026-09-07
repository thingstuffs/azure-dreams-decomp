#include "common.h"
#include "m2c_compat.h"

s16 func_8008D0B8();          /* extern */

typedef struct S_8008CF48_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008CF48_0;   /* arg0 in func_8008CF48 */

s16 func_8008CF48(S_8008CF48_0 *arg0, M2C_UNK arg1) {
    return func_8008D0B8(arg0->unk_02, arg0->unk_06, arg0->unk_0A, arg1);
}
