#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800381D0_0 {
    u8 pad_00[0x1C];
    u8 * unk_1C;
} S_800381D0_0;   /* arg0 in func_800381D0 */


s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_80038288;
extern M2C_UNK func_800382F0;
extern M2C_UNK func_8003832C;

M2C_UNK *func_800381D0(S_800381D0_0 *arg0) {
    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*arg0->unk_1C) != 0) {
            return &func_800382F0;
        }
        return &func_8003832C;
    }
    return &func_80038288;
}
