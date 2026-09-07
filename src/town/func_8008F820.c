#include "common.h"
#include "m2c_compat.h"

s16 func_8008D5C4();                   /* extern */

typedef struct S_8008CF80_0 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8008CF80_0;   /* arg0 in func_8008CF80 */

s16 func_8008CF80(S_8008CF80_0 *arg0) {
    return func_8008D5C4(arg0->unk_02, arg0->unk_06, arg0->unk_0A);
}
