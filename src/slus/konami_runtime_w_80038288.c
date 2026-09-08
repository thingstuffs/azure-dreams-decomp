#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80038288_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    u8 * unk_1C;
} S_80038288_0;   /* arg0 in func_80038288 */


s32 func_80038240();                              /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_800382F0;
extern M2C_UNK func_8003832C;

/* Selects the context's next handler based on its current byte when updates are allowed. */
void func_80038288(S_80038288_0 *context) {
    M2C_UNK *next_handler;

    if (func_80053EF0(4) != 0x100) {
        if (func_80038240(*context->unk_1C) != 0) {
            next_handler = &func_800382F0;
        } else {
            next_handler = &func_8003832C;
        }
        context->unk_10 = next_handler;
    }
}
