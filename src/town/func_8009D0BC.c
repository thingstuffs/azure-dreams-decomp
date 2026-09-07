#include "common.h"
#include "m2c_compat.h"

s16 func_8009A8B0();                   /* extern */
extern M2C_UNK D_8009A8A8;

typedef struct S_8009A81C_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2A];
    s16 unk_36;
    s16 unk_38;
} S_8009A81C_0;   /* arg0 in func_8009A81C */

typedef struct S_8009A81C_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_8009A81C_1;   /* arg1 in func_8009A81C */

void func_8009A81C(S_8009A81C_0 *arg0, S_8009A81C_1 *arg1) {
    u16 temp_a0;

    temp_a0 = arg0->unk_0A - 1;
    arg0->unk_0A = temp_a0;
    arg1->unk_02 = func_8009A8B0((s16) temp_a0, arg1->unk_02, arg0->unk_36);
    arg1->unk_06 = func_8009A8B0((s16) arg0->unk_0A, arg1->unk_06, arg0->unk_38);
    if ((s16) arg0->unk_0A <= 0) {
        arg0->unk_0A = 0x20U;
        arg0->unk_04 = &D_8009A8A8;
    }
}
