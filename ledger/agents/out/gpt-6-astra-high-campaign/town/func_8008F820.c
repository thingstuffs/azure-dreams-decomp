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

/* Pass three signed record components to func_8008D5C4. */
s16 func_8008CF80(S_8008CF80_0 *record) {
    return func_8008D5C4(record->unk_02, record->unk_06, record->unk_0A);
}
