#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A9AFC_2 {
    u8 pad_00[0x73];
    u8 unk_73;
    u8 pad_74[0x7];
    u8 unk_7B;
} S_800A9AFC_2;   /* (arg1 + ((S_800A9AFC_0 *)arg1)->unk_71) in func_800A9AFC */




M2C_UNK func_80042900();             /* extern */
M2C_UNK func_80069F28();     /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */

typedef struct S_800A9AFC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
    u8 pad_6C[0x5];
    u8 unk_71;
    u8 pad_72[0x2];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
    u8 pad_7D[0xB];
    u16 unk_88;
    u16 unk_8A;
} S_800A9AFC_0;   /* arg1 in func_800A9AFC */

typedef struct S_800A9AFC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800A9AFC_1;   /* arg0 in func_800A9AFC */

void func_800A9AFC(S_800A9AFC_1 *arg0, void *arg1) {
    M2C_UNK var_a2;
    M2C_UNK var_a2_2;
    s32 temp_v0;
    u8 temp_s0;
    u8 temp_s1;

    if (((S_800A9AFC_0 *)arg1)->unk_71 & 0x7F) {
        temp_v0 = (s16) func_80042900(arg1, 0x1B);
        if (temp_v0 == 0) {
            M2C_UNK temp_cond;
            u8 temp_a0;
            u8 temp_a1;

            temp_cond = ((S_800A9AFC_0 *)arg1)->unk_1C;
            temp_a0 = arg0->unk_24;
            temp_a1 = arg0->unk_25;
            var_a2 = 0x3000;
            if (temp_cond & 0x2000) {
                var_a2 = 0x300;
            }
            func_8009A3D0(temp_a0, temp_a1, var_a2);
        }
        temp_s0 = ((S_800A9AFC_0 *)arg1)->unk_74;
        temp_s1 = ((S_800A9AFC_0 *)arg1)->unk_7C;
        func_80069F28(arg1 + 0x74, arg1 + 0x75, 0xF);
        ((S_800A9AFC_2 *)((arg1 + ((S_800A9AFC_0 *)arg1)->unk_71)))->unk_73 = (u8) arg0->unk_24;
        ((S_800A9AFC_2 *)((arg1 + ((S_800A9AFC_0 *)arg1)->unk_71)))->unk_7B = (u8) arg0->unk_25;
        arg0->unk_24 = temp_s0;
        arg0->unk_25 = temp_s1;
        ((S_800A9AFC_0 *)arg1)->unk_88 = (u16) ((S_800A9AFC_0 *)arg1)->unk_8A;
        ((S_800A9AFC_0 *)arg1)->unk_2A = (u16) ((S_800A9AFC_0 *)arg1)->unk_6A;
        if (temp_v0 == 0) {
            M2C_UNK temp_cond;
            u8 temp_a0;
            u8 temp_a1;

            temp_cond = ((S_800A9AFC_0 *)arg1)->unk_1C;
            temp_a0 = arg0->unk_24;
            temp_a1 = arg0->unk_25;
            var_a2_2 = 0x3000;
            if (temp_cond & 0x2000) {
                var_a2_2 = 0x300;
            }
            func_8009A21C(temp_a0, temp_a1, var_a2_2);
        }
        ((S_800A9AFC_0 *)arg1)->unk_8A = 0U;
    }
}

/* MECHANISM: An s32 local assigned from an explicit s16 return cast emits the
   one-time sll/sra normalization and holds the result in s4. Rematerializing
   arg1+0x74 plus per-call condition/byte locals produces the retail lw/lbu/lbu order. */
