#include "common.h"
#include "m2c_compat.h"

s32 func_800A0F10();                                /* extern */
s32 func_8009F9A4();                                /* extern */
M2C_UNK func_8009A8EC();                            /* extern */
M2C_UNK func_8009A99C();                            /* extern */
extern M2C_UNK D_800A0CF8;
extern M2C_UNK D_800A0CC0;


typedef struct S_800A0C30_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x1E];
    s16 unk_72;
    u8 pad_74[0x1C];
    s16 unk_90;
} S_800A0C30_0;   /* arg0 in func_800A0C30 */

typedef struct S_800A0C30_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_800A0C30_1;   /* arg2 in func_800A0C30 */

/* Select the tower entry handler according to the six-item tower cap. */
void func_800A0C30(S_800A0C30_0 *script_state, void *unused_context, S_800A0C30_1 *event_params) {
    if (func_800A0F10() != 0) {
        if (func_8009F9A4() < 6) {
            script_state->unk_90 = 6;
            script_state->unk_50 = &D_800A0CF8;
            func_8009A8EC(script_state->unk_72, event_params->unk_02, event_params->unk_06);
            return;
        }
        script_state->unk_50 = &D_800A0CC0;
        func_8009A99C(script_state->unk_72);
    }
}
