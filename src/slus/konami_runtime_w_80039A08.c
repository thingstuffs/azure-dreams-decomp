#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039A08_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039A08_0;   /* arg0 in func_80039A08 */


s32 func_80039884();                          /* extern */
M2C_UNK func_80053DA8();                     /* extern */
s32 func_80053EF0();                         /* extern */
extern M2C_UNK func_800389B4;

/* Updates the state's callback and counter according to the current status. */
void func_80039A08(S_80039A08_0 *state) {
    s32 status;

    status = func_80053EF0(4);
    if (func_80039884(state) != 0) {
        if (status != 0) {
            state->unk_10 = NULL;
            state->unk_1C = (s32) (state->unk_1C - 1);
        }
    } else {
        if (status == 0x100) {
            state->unk_10 = &func_800389B4;
            return;
        }
        func_80053DA8(0xB4);
    }
}
