#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80039A08_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_80039A08_0;   /* arg0 in handle_vm_opcode_06 */


s32 check_state_or_global_flags();                          /* extern */
M2C_UNK SD_Call();                     /* extern */
s32 func_80053EF0();                         /* extern */
void func_800389B4();

/* Rewind a gated script or select its next handler according to runtime status. */
void handle_vm_opcode_06(S_80039A08_0 *state) {
    s32 status;

    status = func_80053EF0(4);
    if (check_state_or_global_flags(state) != 0) {
        if (status != 0) {
            state->unk_10 = NULL;
            state->unk_1C = (s32) (state->unk_1C - 1);
        }
    } else {
        if (status == 0x100) {
            state->unk_10 = &func_800389B4;
            return;
        }
        SD_Call(0xB4);
    }
}
