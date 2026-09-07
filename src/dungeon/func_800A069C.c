#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_800A5F1C();                            /* extern */
M2C_UNK func_800B4C7C(); /* extern */
M2C_UNK func_800C5BBC(); 
typedef struct S_800A5DFC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5DFC_0_pre;   /* the 0x14 bytes before arg0 in func_800A5DFC, addressed as arg0[-1] */

typedef struct S_800A5DFC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 unk_29;
    u16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x4];
    s16 unk_6A;
} S_800A5DFC_0;   /* arg0 in func_800A5DFC */

typedef struct S_800A5DFC_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800A5DFC_1;   /* arg1 in func_800A5DFC */

typedef struct S_800A5DFC_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A5DFC_2;   /* ((S_800A5DFC_0_pre *)arg0)[-1].unk_00 in func_800A5DFC */

/* extern */

void func_800A5DFC(void *arg0, S_800A5DFC_1 *arg1) {
    s32 temp_v1_2;
    s32 var_a2;
    s32 var_s1;
    u8 temp_v1;

    if ((((S_800A5DFC_0 *)arg0)->unk_1C & 0x40) && ((((S_800A5DFC_0 *)arg0)->unk_28 + ((S_800A5DFC_0 *)arg0)->unk_64) >= 2)) {
        temp_v1 = ((S_800A5DFC_0 *)arg0)->unk_29;
        var_a2 = temp_v1 + 0xF;
        ((S_800A5DFC_0 *)arg0)->unk_6A = (s16) (((S_800A5DFC_0 *)arg0)->unk_2A + 0x800);
        if (var_a2 < 0) {
            var_a2 = temp_v1 + 0x1E;
        }
        var_s1 = var_a2 >> 4;
        temp_v1_2 = ((S_800A5DFC_0 *)arg0)->unk_28 + ((S_800A5DFC_0 *)arg0)->unk_64;
        if ((temp_v1_2 - var_s1) <= 0) {
            var_s1 = temp_v1_2 - 1;
        }
        if (var_s1 != 0) {
            ((S_800A5DFC_0 *)arg0)->unk_1C = (s32) (((S_800A5DFC_0 *)arg0)->unk_1C & 0xDFFFFFFF);
            if (!(((S_800A5DFC_2 *)(((S_800A5DFC_0_pre *)arg0)[-1].unk_00))->unk_14 & 0x8000)) {
                func_800B4C7C(3, arg0, (s16) var_s1, 0);
                ((S_800A5DFC_0 *)arg0)->unk_64 = (s16) ((u16) ((S_800A5DFC_0 *)arg0)->unk_64 - var_s1);
                func_800C5BBC(arg1->unk_02, arg1->unk_06, (s16) (arg1->unk_0A - 8), 0x802080, 0x20, 1);
                func_800A5F1C();
                return;
            }
            ((S_800A5DFC_0 *)arg0)->unk_28 = (u8) (((S_800A5DFC_0 *)arg0)->unk_28 - var_s1);
        }
    }
}
