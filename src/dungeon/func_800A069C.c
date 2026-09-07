#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

M2C_UNK func_800A5F1C();                            /* extern */
M2C_UNK func_800B4C7C(); /* extern */
M2C_UNK func_800C5BBC(); 
typedef struct S_800A5DFC_0_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A5DFC_0_pre;   /* the 0x14 bytes before arg0 in func_800A5DFC, addressed as arg0[-1] */


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

    if ((((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0x40) && ((((Rec_D_800E3D7C *)arg0)->unk_28 + ((Rec_D_800E3D7C *)arg0)->unk_64.as_s16) >= 2)) {
        temp_v1 = ((Rec_D_800E3D7C *)arg0)->unk_29;
        var_a2 = temp_v1 + 0xF;
        ((Rec_D_800E3D7C *)arg0)->unk_6A.as_s16 = (s16) (((Rec_D_800E3D7C *)arg0)->unk_2A.as_u16 + 0x800);
        if (var_a2 < 0) {
            var_a2 = temp_v1 + 0x1E;
        }
        var_s1 = var_a2 >> 4;
        temp_v1_2 = ((Rec_D_800E3D7C *)arg0)->unk_28 + ((Rec_D_800E3D7C *)arg0)->unk_64.as_s16;
        if ((temp_v1_2 - var_s1) <= 0) {
            var_s1 = temp_v1_2 - 1;
        }
        if (var_s1 != 0) {
            ((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 = (s32) (((Rec_D_800E3D7C *)arg0)->unk_1C.as_s32 & 0xDFFFFFFF);
            if (!(((S_800A5DFC_2 *)(((S_800A5DFC_0_pre *)arg0)[-1].unk_00))->unk_14 & 0x8000)) {
                func_800B4C7C(3, arg0, (s16) var_s1, 0);
                ((Rec_D_800E3D7C *)arg0)->unk_64.as_s16 = (s16) ((u16) ((Rec_D_800E3D7C *)arg0)->unk_64.as_s16 - var_s1);
                func_800C5BBC(arg1->unk_02, arg1->unk_06, (s16) (arg1->unk_0A - 8), 0x802080, 0x20, 1);
                func_800A5F1C();
                return;
            }
            ((Rec_D_800E3D7C *)arg0)->unk_28 = (u8) (((Rec_D_800E3D7C *)arg0)->unk_28 - var_s1);
        }
    }
}
