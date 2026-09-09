#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800390D0_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_800390D0_0;   /* arg0 in func_800390D0 */


M2C_UNK SD_Call();                     /* extern */
s32 func_80053EF0();                         /* extern */
extern u8 D_80082E6A;
extern M2C_UNK func_80038A00;

/* Selects the next callback or clears it and decrements the state counter. */
void func_800390D0(S_800390D0_0 *state) {
    if (D_80082E6A != 2) {
        if (func_80053EF0(4) != 0x100) {
            SD_Call(0xC4);
            goto set_callback;
        }
        state->unk_10 = NULL;
        state->unk_1C = (s32) (state->unk_1C - 1);
        return;
    }
set_callback:
    state->unk_10 = &func_80038A00;
}
