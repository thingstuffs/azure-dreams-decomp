#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038394_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x1C];
    s16 unk_30;
} S_80038394_0;   /* arg0 in func_80038394 */


s32 func_80033B2C();                             /* extern */
extern M2C_UNK func_80038A10;

void func_80038394(S_80038394_0 *arg0) {
    if (func_80033B2C(arg0->unk_30) != 0) {
        arg0->unk_10 = &func_80038A10;
    }
}
